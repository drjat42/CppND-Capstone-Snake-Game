#ifndef RANDOM_BOARD_LOADER_H
#define RANDOM_BOARD_LOADER_H

#include "board.h"
#include "board_loader.h"

class RandomBoardLoader : public BoardLoader {

public:
  RandomBoardLoader(size_t gridWidth, size_t gridHeight, size_t maxObstacles);
  ~RandomBoardLoader();

protected:
  Board LoadBoard();
 
private:
  const size_t _gridWidth;
  const size_t _gridHeight;
  const size_t _maxObstacles;

};

#endif