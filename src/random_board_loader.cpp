
#include <random>
#include "random_board_loader.h"

// BoardLoader that makes boards with obstacles at random locations.
RandomBoardLoader::RandomBoardLoader(size_t gridWidth, size_t gridHeight, size_t maxObstacles) : 
  _gridWidth(gridWidth), _gridHeight(gridHeight), _maxObstacles(maxObstacles) {}

RandomBoardLoader::~RandomBoardLoader() {}

Board RandomBoardLoader::LoadBoard(){  
  std::vector<SDL_Point> obstacles;
  srand (time(NULL));
  std::random_device rd;
  std::mt19937 mersenne_twister(rd());
  std::uniform_int_distribution<> widhtDist(0, _gridWidth);
  std::uniform_int_distribution<> heightDist(0, _gridHeight);
  for (int ii = 0; ii < _maxObstacles; ii++) {
    int x = widhtDist(mersenne_twister);
    int y = heightDist(mersenne_twister);
    obstacles.push_back(SDL_Point{x,y});
  }
  Board board = Board(obstacles);
  return board;  
}