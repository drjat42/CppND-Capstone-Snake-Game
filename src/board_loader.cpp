#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <thread>
#include "board_loader.h"


/* Implementation of class "MessageQueue" (from my  Concurrent Traffic Simulation TrafficLight implementation) */ 
template <typename T>
T MessageQueue<T>::receive()
{
    std::unique_lock<std::mutex> uLock(_mutex);
    _condition.wait(uLock, [this] { return !_queue.empty(); });

    T msg = std::move(_queue.back());
    _queue.pop_back();

  return msg;
}

template <typename T>
void MessageQueue<T>::send(T &&msg)
{
    std::lock_guard<std::mutex> uLock(_mutex);
    _queue.clear();
    _queue.emplace_back(msg); 
    _condition.notify_one();
}

/* Implementation of class "BoardLoader" */
BoardLoader::BoardLoader() {}
BoardLoader::~BoardLoader() 
{
    // Wait for threads to exit.
    std::for_each(_threads.begin(), _threads.end(), [](std::thread &t) {
        t.join();
    });
}

std::promise<void> BoardLoader::StartBoardLoadingThread()
{
    std::promise<void> prmsIsGameOver;
    std::future<void> ftrIsGameOver = prmsIsGameOver.get_future();
    _threads.emplace_back(std::thread(&BoardLoader::LevelTimer, this, std::move(ftrIsGameOver)));
    return std::move(prmsIsGameOver);
}

/*
 At random intervals, check if the game is over.
 If so, exit.
 If not load a new board and send it to the game.
*/
void BoardLoader::LevelTimer(std::future<void> ftrIsGameOver)
{
    srand (time(NULL));
    int levelLengthMS;
    std::chrono::time_point<std::chrono::steady_clock> now;
    std::chrono::time_point<std::chrono::steady_clock> levelEnd;
    std::random_device rd;
    std::mt19937 mersenne_twister(rd());
    std::uniform_int_distribution<> dist(MIN_BOARD_MS_k, MAX_BOARD_MS_k);
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
        //_messages.send(std::move(board));
        _board = std::move(board);
        uLock.unlock();
    }
 }

 const Board & BoardLoader::getBoard() {
     std::unique_lock<std::mutex> uLock(_mutex);
     return _board;
 }