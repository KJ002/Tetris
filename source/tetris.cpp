#include "tetris.hpp"
#include "models.hpp"
#include "object.hpp"
#include <raylib.h>

#include <iostream>
#define LOG(x) std::cout << x << std::endl

Tetris::Tetris(
  int screenWidth,
  int screenHeight,
  char * title,
  int screenFPS,
  bool debug
):
  display(screenWidth, screenHeight, title, screenFPS)
{
  this->debug = debug;
  cleanGlobalMap();
}

void Tetris::spawnShape(){
  TetrisBlock * x = new TetrisBlock((GetScreenWidth()/2)-20, 10, 1);


  currentBlockBuffer = 0;

  current = x;
  shapes.push_back(x);
  display.attachShape(x);
}

void Tetris::moveDown(){
  current->meta.appendY(10);
}

void Tetris::moveLeft(){
  current->meta.appendX(-10);
}

void Tetris::moveRight(){
  current->meta.appendX(10);
}

void Tetris::deltaMoveDown(){
  currentBlockBuffer += 10*((debug) ? .01667 : deltaTime);

  if (currentBlockBuffer >= 10){
    moveDown();
    currentBlockBuffer-=10;
  }
}

void Tetris::rotate(){
  current->rotateRight();
}

bool Tetris::hasPassedYAxis(){
  int i = 25;
  bool foundLowestIndex = false;

  while (i && !foundLowestIndex){
    i--;
    foundLowestIndex = current->meta.map[i];
  }

  return current->getPosition(i).y+10 >= GetScreenHeight();
}

bool Tetris::hasCollided(){
  for (TetrisBlock* other : shapes){
    if (other != current && current->colliding(other)) return true;
  }

  return false;
}

void Tetris::cleanGlobalMap(){
  for (int i = 0; i < 200; i++)
    globalMap[i] = 0;
}

int Tetris::posToIndex(int x, int y){
  // Correct data
  // x and y must ALWAYS be a multiple
  // of 10 for this to work but due to the
  // nature of tetris this should be fine

  x = x/10;
  y = y/10;

  // Calculate index position

  return (y*10)+x;
}

int Tetris::posToIndex(Vec2 v){
  // Correct data
  // x and y must ALWAYS be a multiple
  // of 10 for this to work but due to the
  // nature of tetris this should be fine

  v.x = v.x/10;
  v.y = v.y/10;

  // Calculate index position

  return (v.y*10)+v.x;
}

bool Tetris::currentWillCollide(int direction){

  for (int i = 0; i < 25; i++){
    if (current->meta.map[i]){
      Vec2 position = current->getPosition(i);
      position.x += direction;

      if (globalMap[posToIndex(position)])
        return true;
    }
  }

  return false;
}

void Tetris::updateGlobalMap(){
  cleanGlobalMap();

  for (TetrisBlock* object : shapes){
    if (object != current){
      for (int i = 0; i < 25; i++){
        if (object->meta.map[i]){
          int index = posToIndex(object->getPosition(i));

          globalMap[index] = 1;
        }
      }
    }
  }
}

std::vector<int> Tetris::getFullLines(){
  std::vector<int> result;

  for (int i = 0; i < 200; i+=10){
    int total = 0;

    for (int x = 0; x < 10; x++){
      total += globalMap[i+x];
    }

    if (total == 10)
      result.push_back(i);
  }

  return result;
}

void Tetris::start(){
  spawnShape();

  while (!WindowShouldClose()){
    deltaTime = GetTime() - lastTime;
    lastTime = GetTime();

    if (hasPassedYAxis() || hasCollided()) spawnShape();

    updateGlobalMap();

    // Game drawing loop

    BeginDrawing();
    ClearBackground(RAYWHITE);
    display.drawShape();
    EndDrawing();

    if (IsKeyPressed(KEY_A) + IsKeyPressed(KEY_D) + IsKeyPressed(KEY_S) < 2){
      if (IsKeyPressed(KEY_W)) rotate();

      if (IsKeyPressed(KEY_A) &&
          !currentWillCollide(-10))
        moveLeft();

      if (IsKeyPressed(KEY_D) &&
          !currentWillCollide(10))
        moveRight();

      if (IsKeyPressed(KEY_S)) moveDown();
    }

    deltaMoveDown();

  }

  display.closeScreen();
}
