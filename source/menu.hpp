#pragma once
#include "display.hpp"
#include "object.hpp"
#include <raylib.h>

class Menu{
private:
  Display* display;
  bool debug;

  bool startGame = false;

public:
  bool shouldStartGame();

  Button button = Button("Play",
                         Vec2((float)GetScreenWidth()/2,
                              (float)GetScreenHeight()/2),
                         Vec2(40.f, 14.f),
                         10);

  Menu(
    Display* display = nullptr,
    bool debug = false
  );

  void update();
};
