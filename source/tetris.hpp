#pragma once
#include "display.hpp"
#include <vector>

class Tetris{
private:
  Display display;
  std::vector<Object*> shapes;
  Object* current;

  void spawnShape();

public:
  Tetris(
    int screenWidth,
    int screenHeight,
    char * title,
    int screenFPS = 60
  );

  void start();

};
