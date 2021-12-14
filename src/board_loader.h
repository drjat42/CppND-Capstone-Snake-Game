#ifndef BOARD_LOADER_H
#define BOARD_LOADER_H

#include <condition_variable>
#include <deque>
#include <future>
#include <mutex>
#include <thread>
#include <vector>
#include "board.h"

constexpr int kMIN_BOARD_MS = 10000; // Minimum number of milliseconds between successive boards
constexpr int kMAX_BOARD_MS = 15000; // Maximum number of milliseconds between successive boards

// Abstract class to load boards at random intervals and send them to the game until the game ends.
class BoardLoader {

public:
  BoardLoader();
  ~BoardLoader();

  // Start the thread that will load boards.
  std::promise<void> StartBoardLoadingThread();

  // Getter
  const Board & getBoard();
  
protected:
  // Pure virutal function to load the next board.  
  virtual Board LoadBoard() = 0;
  
 private:
  // Load boards at random intervals 
  void  LevelTimer(std::future<void> ftrIsGameOver);

  std::mutex               _mutex;  // Control access to _board
  Board                    _board;
  std::vector<std::thread> _threads; 
};

#endif