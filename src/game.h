#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "board_loader.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"

class Game {
 public:
  Game(const std::size_t grid_width, const std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer, BoardLoader &loader,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

 private:
  Snake snake;
  SDL_Point food;
  Board board;
  

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  void PlaceFood();
  bool Update();
};

#endif