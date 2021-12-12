#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "SDL.h"

class Board {

public:
  const std::vector<SDL_Point> & Obstacles() const;

  // Rule of Five
  Board();                                       // No-obstacles constructor
  Board(std::vector<SDL_Point> obstacles);       // Constructor
  ~Board();                                      // Destructor
  Board(const Board &Other) = delete;            // Copy Constructor. Board is unique. Disallow copying.
  Board &operator=(const Board &Other) = delete; // Copy Assignment Operator.  Board is unique.  Disallow copying.
  Board(Board &&other);                          // Move constructor
  Board &operator=(Board &&other);               // Move Assignment Operator

 private:
  std::vector<SDL_Point> _obstacles;
};

#endif