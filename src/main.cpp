#include <iostream>
#include "controller.h"
#include "file_board_loader.h"
#include "game.h"
#include "random_board_loader.h"
#include "renderer.h"

void usage(char *prog) {
  std::cerr << "Usage " << prog << " random | file " << std::endl;
  exit(1);
}

int main(int argc, char *argv[]) {

  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};
  constexpr std::size_t kMaxObstacles{15}; // Maximum number of random obstacles
  const     std::string kRandomLoaderArg = "random"; // Commandline arg to select random board loader
  const     std::string kFileLoaderArg   = "file";   // Commandline arg to select file board laoder
  const     std::string kBoardDirectoryPath{"../data"};

  // Parrse commandline parameters to select board loader to use
  bool useFileBoardLoader = true;  // default
  if (argc > 2 
      || (argc == 2 &&  argv[1] == kRandomLoaderArg)) {
    useFileBoardLoader = false;
  } else if (argc > 2 
             || (argc == 2 && argv[1] != kFileLoaderArg)) {
    usage(argv[0]);
  }

  FileBoardLoader fileBoardLoader(kBoardDirectoryPath);
  RandomBoardLoader randomBoardLoader(kGridWidth, kGridHeight, kMaxObstacles);
  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);
  if (useFileBoardLoader) {  // This is ugly. I'd rather assig
    game.Run(controller, renderer, fileBoardLoader, kMsPerFrame);
  } else {
    game.Run(controller, renderer, randomBoardLoader, kMsPerFrame);
  }
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  return 0;
}