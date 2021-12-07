#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "SDL.h"

class Board {
 public:

  Board(int grid_width, int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height) {
            SDL_Point obstalce{5, 5};
            obstacles.push_back(obstalce);
        }



  std::vector<SDL_Point> obstacles;

 private:
  int grid_width;
  int grid_height;
};

#endif