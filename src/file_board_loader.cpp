#include <dirent.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include "file_board_loader.h"

/* 
* BoardLoader that loads boards from files. 
* Loads the paths to all files in the directory named by  boardDirectoryPath 
* into _boardPaths.  
* _nextBoardIndex is implicitly set to 0.
*/
FileBoardLoader::FileBoardLoader(std::string boardDirectoryPath) {
  DIR *directory = opendir(boardDirectoryPath.c_str());
  struct dirent *file;
  if (directory == nullptr) {
    std::cerr << "Unable to open board directory path" << boardDirectoryPath << ". Please check the path to game boards." << std::endl;
    return; 
  }
  while ((file  = readdir(directory)) != nullptr) {
     if (file->d_type != DT_REG) {
       continue; // Skip files that aren't boards like "." and "..""
     }  
     std::string filePath = boardDirectoryPath + "/" + file->d_name;
     _boardPaths.push_back(filePath);
  }
  closedir(directory);
}

/* Destructor */
FileBoardLoader::~FileBoardLoader(){}

/* 
* Load the next board from disk.   
* Increment the next board index.
*/
Board FileBoardLoader::LoadBoard() {  
   std::string line;
  int x;
  int y;
  char sep;
  std::vector<SDL_Point> obstacles;
  std::ifstream filestream{_boardPaths[_nextBoardIndex]};
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> x >> sep >> y) {
        obstacles.push_back(SDL_Point{x,y});
      }
    }
  }
  Board board = Board(obstacles);
  _nextBoardIndex = (_nextBoardIndex + 1) % _boardPaths.size();
  return board;  
}