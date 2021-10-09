#pragma once
#include "display.hpp"
#include "object.hpp"
#include <vector>

class Tetris{
private:
  Display display;
  std::vector<TetrisBlock*> shapes;
  TetrisBlock* current;

  void spawnShape();
  void moveDown();

public:
  Tetris(
    int screenWidth,
    int screenHeight,
    char * title,
    int screenFPS = 60
  );

  void start();

};