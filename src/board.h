#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <vector>
#include "SDL.h"

class Board {

public:
  Board(std::string const path, int const grid_width, int const grid_height);
  std::vector<SDL_Point> Obstacles();

 private:
  void ReadObstacles(std::string const path);

  const std::string path;
  std::vector<SDL_Point> obstacles;
  const int grid_width;
  const int grid_height;
};

#endif