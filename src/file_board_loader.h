#ifndef FILE_BOARD_LOADER_H
#define FILE_BOARD_LOADER_H

#include <string>
#include "board.h"
#include "board_loader.h"

class FileBoardLoader : public BoardLoader {

public:
  FileBoardLoader(std::string boardDirectoryPath);
  ~FileBoardLoader();


protected:
  Board LoadBoard();
 
private:
  void ReadObstacles(std::string const path);
  
  int _nextBoardIndex;
  std::vector<std::string> _boardPaths;

};

#endif