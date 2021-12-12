
#include <fstream>
#include <sstream>
#include <iostream>
#include "file_board_loader.h"

// BoardLoader that loads boards from files.
// TODO: load from files in a directory
//       remember last file name loaded, 
//       rotate through alphabetically
FileBoardLoader::FileBoardLoader(std::string path): _path(path) {}
FileBoardLoader::~FileBoardLoader(){}
Board FileBoardLoader::LoadBoard() {  
   std::string line;
  int x;
  int y;
  char sep;
  std::vector<SDL_Point> obstacles;
  std::cerr << "Reading obstacles from " << _path << std::endl;
  std::ifstream filestream(_path);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> x >> sep >> y) {
        std::cerr << "Obstacle at " << x << ", " << y << std::endl;
        obstacles.push_back(SDL_Point{x,y});
      }
    }
  }
  Board board = Board(obstacles);
  return std::move(board);  
}