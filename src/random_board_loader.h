#ifndef RANDOM_BOARD_LOADER_H
#define RANDOM_BOARD_LOADER_H

#include "board.h"
#include "board_loader.h"

class RandomBoardLoader : public BoardLoader {

public:
  RandomBoardLoader(int maxObstacles);
  ~RandomBoardLoader();

protected:
  Board LoadBoard();
 
private:
  const int _maxObstacles;

};

#endif