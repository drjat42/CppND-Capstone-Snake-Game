#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "SDL.h"

class Board {

public:
  const std::vector<SDL_Point> & Obstacles() const;

  // Rule of Five
  Board();                                       // Default, no-obstacles constructor
  Board(std::vector<SDL_Point> obstacles);       // Constructor with obstacles
  ~Board();                                      // Destructor
  Board(const Board &Other);                     // Copy Constructor
  Board &operator=(const Board &Other);          // Copy Assignment Operator
  Board(Board &&other);                          // Move constructor
  Board &operator=(Board &&other);               // Move Assignment Operator

 private:
  std::vector<SDL_Point> _obstacles;
};

#endif