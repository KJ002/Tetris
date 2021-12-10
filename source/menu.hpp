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

  Button button = Button("Play", Vec2(0.f, 0.f), 10, RAYWHITE, 0, 0);

  Menu(
    Display* display = nullptr,
    bool debug = false
  );

  void update();
};
