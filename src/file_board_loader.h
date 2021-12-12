#ifndef FILE_BOARD_LOADER_H
#define FILE_BOARD_LOADER_H

#include <string>
#include "board.h"
#include "board_loader.h"

class FileBoardLoader : public BoardLoader {

public:
  FileBoardLoader(std::string path);
  ~FileBoardLoader();


protected:
  Board LoadBoard();
 
private:
  void ReadObstacles(std::string const path);

  const std::string _path;

};

#endif