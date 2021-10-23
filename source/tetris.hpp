#pragma once
#include "display.hpp"
#include "object.hpp"
#include "models.hpp"
#include <vector>

class Tetris{
private:
  bool debug;

  Display display;

  std::vector<TetrisBlock*> shapes;
  TetrisBlock* current;
  std::array<bool, 200> globalMap;

  double lastTime = GetTime();
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
  int posToIndex(Vec2 v);
  bool currentWillCollide(int direction);
  void updateGlobalMap();
  std::vector<int> getFullLines();
  void purgeFullLines(std::vector<int> y);
  void adjustLines(std::vector<int> y);
  bool currentWillBeOut(char direction = 'L');

public:
  Tetris(
    int screenWidth,
    int screenHeight,
    char * title,
    int screenFPS = 60,
    bool debug = false
  );

  void start();
};
