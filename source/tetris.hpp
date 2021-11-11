#pragma once
#include "display.hpp"
#include "object.hpp"
#include "models.hpp"
#include <vector>
#include <raylib.h>

class Tetris{
private:
  bool debug;

  Display display;

  std::vector<TetrisBlock*> shapes;
  TetrisBlock* current;
  std::array<bool, 200> globalMap;
  Vec2 spawnPosition = {(float)(GetScreenWidth()/2)-20, (float)0};

  int score = 0;

  Vec2 scoreObjNEPos = {50, 50};
  Text scoreObj = {"0", scoreObjNEPos, 11, RAYWHITE};

  double lastTime = GetTime();
  double deltaTime;

  float currentBlockBuffer = 0;

  void spawnShape();
  void moveDown();
  void moveLeft();
  void moveRight();
  void deltaMoveDown();
  void rotate();
  void correctPosition();

  bool hasPassedYAxis();
  bool hasCollided();
  void cleanGlobalMap();
  int posToIndex(int x, int y);
  int posToIndex(Vec2 v);
  bool currentWillCollide(Vec2 direction);
  bool currentCanRotate();
  void updateGlobalMap();
  std::vector<int> getFullLines();
  void purgeFullLines(std::vector<int> y);
  void adjustLines(std::vector<int> y);
  void correctLines(std::vector<int> y);
  void updateScore(std::vector<int> y);
  void updateScorePosition();
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
