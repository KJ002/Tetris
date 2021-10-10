#pragma once
#include "display.hpp"
#include "object.hpp"
#include "models.hpp"
#include <chrono>
#include <vector>

class Tetris{
private:
  Display display;
  std::vector<TetrisBlock*> shapes;
  TetrisBlock* current;

  timePoint lastTime;
  std::chrono::duration<double> deltaTimeDur;
  double deltaTime;

  void spawnShape();
  void moveDown();
  void moveLeft();
  void moveRight();
  void deltaMoveDown();
  void rotate();

public:
  Tetris(
    int screenWidth,
    int screenHeight,
    char * title,
    int screenFPS = 60
  );

  void start();
};
