#include "board.h"

Board::Board() {}
Board::~Board() {}

Board::Board(std::vector<SDL_Point> obstacles) : _obstacles(obstacles) {}

Board::Board(Board &&other) {
  _obstacles = other._obstacles;
  other._obstacles.clear();
}                       

Board & Board::operator=(Board &&other) {
  _obstacles = other._obstacles;
  other._obstacles.clear();
}

const std::vector<SDL_Point> & Board::Obstacles() const {
    return _obstacles;
};
