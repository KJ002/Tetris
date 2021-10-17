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
  std::array<bool, 200> globalMap;

  timePoint lastTime;
  std::chrono::duration<double> deltaTimeDur;
  double deltaTime;

  float currentBlockBuffer = 0;

  void spawnShape();
  void moveDown();
  void moveLeft();
  void moveRight();
  void deltaMoveDown();
  void rotate();

  bool hasPassedYAxis();
  bool hasCollided();
  void cleanGlobalMap();
  int posToIndex(int x, int y);
  void updateGlobalMap();

public:
  Tetris(
    int screenWidth,
    int screenHeight,
    char * title,
    int screenFPS = 60
  );

  void start();
};
