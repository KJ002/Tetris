#pragma once
#include "display.hpp"
#include "object.hpp"
#include <raylib.h>

class Menu{
private:
  Display* display;
  bool debug;

  bool startGame = false;

  float buttonTextWidth = MeasureText((char*)"Play", 14);

public:
  bool shouldStartGame();

  Square button = Square(GetScreenWidth()/2-((buttonTextWidth+4)/2), GetScreenHeight()/2+7, buttonTextWidth+4, 16);
  Text buttonText = Text(
    "Play",
    Vec2((float)GetScreenWidth()/2-(buttonTextWidth/2),
    (float)GetScreenHeight()/2+6),
    15,
    (Color){255, 255, 255, 255}
  );

  Menu(
    Display* display = nullptr,
    bool debug = false
  );

  void update();
};
