#pragma once
#include "display.hpp"
#include "object.hpp"
#include "models.hpp"
#include <vector>
#include <raylib.h>

class Tetris{
private:
  bool debug;

  Display* display;

  std::vector<TetrisBlock*> shapes;
  TetrisBlock* current = NULL;
  TetrisBlock currentFuture = {0, 0, 0};
  std::array<bool, 200> globalMap;
  std::vector<int> fullLines;
  Vec2 spawnPosition = {(float)(GetScreenWidth()/2)-20, (float)0};

  int score = 0;

  Vec2 scoreObjNEPos = {90, 10};
  Text* scoreObj = new Text("0", scoreObjNEPos, 10, RAYWHITE);
  std::vector<Text*> pastScores;

  double lastTime = -1;
  double deltaTime;

  float currentBlockBuffer = 0;

  void spawnShape();
  void moveDown(TetrisBlock* block);
  void moveLeft(TetrisBlock* block);
  void moveRight(TetrisBlock* block);
  void deltaMoveDown();
  void rotate(TetrisBlock* block);
  void correctPosition();
  void autoplace(TetrisBlock* block);

  bool isCollideYAxis(TetrisBlock* block);
  void cleanGlobalMap();
  int posToIndex(int x, int y);
  int posToIndex(Vec2 v);
  bool willCollide(TetrisBlock* block, Vec2 direction);
  bool canRotate(TetrisBlock* block);
  void updateGlobalMap();
  void getFullLines();
  void purgeFullLines();
  void correctLines();
  void updateScore();
  void updateScorePosition();
  bool willBeOut(TetrisBlock* block, char direction = 'L');
  bool shouldGameOver();
  void clearBoard();
  void updateScores();
  void updateFutureCurrent();

public:
  Tetris(
    Display* screenDisplay = nullptr,
    bool debug = false
  );

  const std::vector<TetrisBlock*>* exposeTetrisBlocks() const;
  const int getScore() const;
  void update();
};
