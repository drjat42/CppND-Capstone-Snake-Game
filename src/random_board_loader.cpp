
#include "random_board_loader.h"

// BoardLoader that makes boards with obstacles at random locations.
RandomBoardLoader::RandomBoardLoader(int maxObstacles): _maxObstacles(maxObstacles) {}
RandomBoardLoader::~RandomBoardLoader() {}
Board RandomBoardLoader::LoadBoard(){  
  std::vector<SDL_Point> obstacles;
  // TODO
  Board board = Board(obstacles);
  return board;  
}