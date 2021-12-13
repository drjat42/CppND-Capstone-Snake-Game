#ifndef BOARD_LOADER_H
#define BOARD_LOADER_H

#include <condition_variable>
#include <deque>
#include <future>
#include <mutex>
#include <thread>
#include <vector>
#include "board.h"

constexpr int MIN_BOARD_MS_k = 10000; // Minimum number of milliseconds between successive boards
constexpr int MAX_BOARD_MS_k = 15000; // Maximum number of milliseconds between successive boards

// MessageQueue from my Concurrent Traffic Simulation TrafficLight implementation
template <class T>
class MessageQueue
{
public:
    T receive();
    void send(T &&msg);

private:
    std::deque<T> _queue;
    std::condition_variable _condition;
    std::mutex _mutex;    
};


// Abstract class to load boards at random intervals and send them to the game until the game ends.
class BoardLoader {

public:
  BoardLoader();
  ~BoardLoader();

  // Start the thread that will load boards.
  std::promise<void> StartBoardLoadingThread();
  const Board & getBoard();
  
protected:
  // Pure virutal function to load the next board.  
  virtual Board LoadBoard() = 0;
  
 private:
  void  LevelTimer(std::future<void> ftrIsGameOver);

  std::mutex               _mutex;  // Control access to _board
  Board                    _board;
  MessageQueue<Board>      _messages;
  std::vector<std::thread> _threads; 
};

#endif