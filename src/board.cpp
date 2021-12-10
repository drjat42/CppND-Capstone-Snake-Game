#include "board.h"
#include <fstream>
#include<sstream>
#include <iostream>

Board::Board(std::string const path, int const grid_width, int const grid_height) : grid_width(grid_width), grid_height(grid_height) {
    ReadObstacles(path);
}

void Board::ReadObstacles(std::string const path) {
  std::string line;
  int x;
  int y;
  char sep;
  std::cerr << "Reading obstacles from " << path << std::endl;
  std::ifstream filestream(path);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> x >> sep >> y) {
        std::cerr << "Obstacle at " << x << ", " << y << std::endl;
        obstacles.push_back(SDL_Point{x,y});
      }
    }
  }
}

std::vector<SDL_Point> Board::Obstacles() {
    return obstacles;
};
