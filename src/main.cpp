#include <iostream>
#include "controller.h"
#include "file_board_loader.h"
#include "game.h"
#include "random_board_loader.h"
#include "renderer.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};
  constexpr std::size_t kMaxObstacles{15}; // Maximum number of random obstacles
  const     std::string kBoardDirectoryPath{"../data"};

  FileBoardLoader fileBoardLoader(kBoardDirectoryPath);
  RandomBoardLoader randomBoardLoader(kGridWidth, kGridHeight, kMaxObstacles);
  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);
  game.Run(controller, renderer, randomBoardLoader, kMsPerFrame);
//  game.Run(controller, renderer, fileBoardLoader, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  return 0;
}