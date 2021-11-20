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
  TetrisBlock* current = NULL;
  std::array<bool, 200> globalMap;
  std::vector<int> fullLines;
  Vec2 spawnPosition = {(float)(GetScreenWidth()/2)-20, (float)0};

  int score = 0;

  Vec2 scoreObjNEPos = {90, 10};
  Text* scoreObj = new Text("0", scoreObjNEPos, 10, RAYWHITE);
  std::vector<Text*> pastScores;

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
  void autoplace();

  bool hasPassedYAxis();
  void cleanGlobalMap();
  int posToIndex(int x, int y);
  int posToIndex(Vec2 v);
  bool currentWillCollide(Vec2 direction);
  bool currentCanRotate();
  void updateGlobalMap();
  void getFullLines();
  void purgeFullLines();
  void correctLines();
  void updateScore();
  void updateScorePosition();
  bool currentWillBeOut(char direction = 'L');
  bool shouldGameOver();
  void clearBoard();
  void updateScores();

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
