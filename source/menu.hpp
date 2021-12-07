#pragma once
#include "display.hpp"
#include "object.hpp"

class Menu{
private:
  Display* display;
  bool debug;

  bool startGame = false;

public:
  bool shouldStartGame();
  Square button = Square(0, 0, 10, 10);

  Menu(
    Display* display = nullptr,
    bool debug = false
  );

  void update();
};
