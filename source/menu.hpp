#pragma once
#include "display.hpp"
#include "object.hpp"
#include "tetris.hpp"
#include <raylib.h>

class Menu{
private:
  Display* display;
  Tetris* game;
  bool debug;

  std::vector<TetrisBlock*> tetrisBlocks;

public:
  bool shouldStartGame();

  Button button = Button("Play",
                         Vec2((float)GetScreenWidth()/2,
                              (float)GetScreenHeight()/2),
                         Vec2(40.f, 14.f),
                         10);

  Menu(
    Display* display = nullptr,
    Tetris* game = nullptr,
    bool debug = false
  );

  void update();
};
