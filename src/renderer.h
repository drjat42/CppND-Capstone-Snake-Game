#ifndef RENDERER_H
#define RENDERER_H

#include "board.h"
#include <vector>
#include "SDL.h"
#include "snake.h"


struct Color {
int r;
int g;
int b;
int a;
};

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(Snake const snake, Board const board, SDL_Point const &food);
  void UpdateWindowTitle(int score, int fps);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;

  const Color bgC = Color{ 0x1E, 0x1E, 0x1E, 0xFF }; // Background
  const Color hC  = Color{ 0x00, 0x7A, 0xCC, 0xFF }; // Head - alive
  const Color dC  = Color{ 0xFF, 0x00, 0x00, 0xFF }; // Head - dead
  const Color bC  = Color{ 0xFF, 0xFF, 0xFF, 0xFF }; // Body
  const Color fC  = Color{ 0xFF, 0xCC, 0x00, 0xFF }; // Food
  const Color oC  = Color{ 0xFF, 0x00, 0xFF, 0xFF }; // Obstables
};

#endif