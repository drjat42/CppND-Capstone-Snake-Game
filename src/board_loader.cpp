#include <algorithm>
#include <chrono>
#include <random>
#include <thread>
#include "board_loader.h"


/* Implementation of class "BoardLoader" */
BoardLoader::BoardLoader() {}
BoardLoader::~BoardLoader() 
{
    // Wait for threads to exit.
    std::for_each(_threads.begin(), _threads.end(), [](std::thread &t) {
        t.join();
    });
}

/* 
 * Begin loading boards in a new thread. 
 * Return a promise that the main thread can use to tell the loader when the game has ended.
 * The loader thread will then exit.
 */
std::promise<void> BoardLoader::StartBoardLoadingThread()
{
    std::promise<void> prmsIsGameOver;
    std::future<void> ftrIsGameOver = prmsIsGameOver.get_future();
    _threads.emplace_back(std::thread(&BoardLoader::LevelTimer, this, std::move(ftrIsGameOver)));
    return std::move(prmsIsGameOver);
}

/*
 * Loop indefinitely loading boards at intervals of randomly varying length.
 * Before loading each board, check if the parameter future is ready.
 * If so, return.  
 */
void BoardLoader::LevelTimer(std::future<void> ftrIsGameOver)
{
    srand (time(NULL));
    int levelLengthMS;
    std::chrono::time_point<std::chrono::steady_clock> now;
    std::chrono::time_point<std::chrono::steady_clock> levelEnd;
    std::random_device rd;
    std::mt19937 mersenne_twister(rd());
    std::uniform_int_distribution<> dist(kMIN_BOARD_MS, kMAX_BOARD_MS);
    while (true) {
        levelLengthMS = dist(mersenne_twister);
        now =  std::chrono::steady_clock::now();
        levelEnd = now +  std::chrono::milliseconds(levelLengthMS);

        while (now <= levelEnd) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            now =  std::chrono::steady_clock::now();
        }

        if (ftrIsGameOver.wait_for(std::chrono::seconds(0))  == std::future_status::ready) {
            // Game is over.
            break;
        }
        
         // Loading a board might be slow.
         // Don't hold a lock while loading.
        Board board = LoadBoard(); 

        std::unique_lock<std::mutex> uLock(_mutex);
        _board = std::move(board);
        uLock.unlock();
    }
 }

 /* Return the current board. */
 const Board & BoardLoader::getBoard() {
     std::lock_guard<std::mutex> gLock(_mutex);
     return _board;
 }