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
  Square button = Square(GetScreenWidth()/2-5, GetScreenHeight()/2-5, 10, 10);

  Menu(
    Display* display = nullptr,
    bool debug = false
  );

  void update();
};
