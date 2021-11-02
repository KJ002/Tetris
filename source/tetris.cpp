#include "tetris.hpp"
#include "models.hpp"
#include "object.hpp"
#include <raylib.h>
#include <algorithm>
#include <vector>
#include <cstdlib>

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
  TetrisBlock * x = new TetrisBlock(spawnPosition.x, spawnPosition.y, rand());

  // Correct current position spawn to top of current

  int top;

  for (int i = 0; i < 25; i++){
    if (x->meta.map[i]){
      top = i;
      break;
    }
  }

  x->meta.appendY(-(x->getPosition(top).y));

  // Clean up previous current values

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

void Tetris::correctPosition(){
  double time = GetTime();

  while (time+1 > GetTime()){
    if (IsKeyPressed(KEY_A) + IsKeyPressed(KEY_D) < 2){
      if (IsKeyPressed(KEY_A) &&
          !currentWillCollideX(-10) &&
          !currentWillBeOut('L'))
        moveLeft();

      if (IsKeyPressed(KEY_D) &&
          !currentWillCollideX(10) &&
          !currentWillBeOut('R'))
        moveRight();
    }

    BeginDrawing();
    ClearBackground(BLACK);
    display.drawShape();
    EndDrawing();

  }
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

bool Tetris::currentWillCollideX(int direction){

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

bool Tetris::currentWillCollideY(int direction){
  TetrisBlock future = *current;

  future.meta.appendY(direction);

  for (TetrisBlock* other : shapes){
    if (other != current && future.colliding(other)) return true;
  }

  return false;
}

bool Tetris::currentCanRotate(){
  TetrisBlock future = *current;

  future.rotateRight();

  for (TetrisBlock* other : shapes){
    if (other != current && future.colliding(other)) return false;
  }

  for (int i = 0; i < 25; i++){
    if(future.meta.map[i] &&
       (future.getPosition(i).x < 0 ||
        future.getPosition(i).x >= 100 ||
        future.getPosition(i).y < 0 ||
        future.getPosition(i).y > 200))
      return false;
  }

  return true;

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

void Tetris::purgeFullLines(std::vector<int> y){
  for (TetrisBlock* x : shapes){
    for (int i = 0; i < 25; i++){
      if (std::find(y.begin(), y.end(), x->getPosition(i).y) != y.end()){
        x->meta.map[i] = false;
      }
    }
  }
}

void Tetris::adjustLines(std::vector<int> y){
  for (int x : y){
    for (TetrisBlock* shape : shapes){
      for (int i = 24; i >= 0; i--){
        if (shape->meta.map[i] && shape->getPosition(i).y < x){
          shape->meta.appendY(10);
          break;
        }
      }
    }
  }
}

void Tetris::correctLines(std::vector<int> y){
  for (int x : y){
    for (TetrisBlock* shape : shapes){

      if (shape == current)
        continue;

      bool doesIntersect = false;
      int lastValid = 0;
      int lastTrueValid = 25;

      for (int i = 24; i >= 0; i--){
        if (lastTrueValid == 25 && shape->meta.map[i])
          lastTrueValid = i;
        if (shape->getPosition(i).y == x){
          doesIntersect = true;
          lastValid = i;
          break;
        }
      }

      if (doesIntersect){
        for (int i = 24; i >= 0; i--){
          if (i < lastValid && shape->meta.map[i]){
            shape->meta.map[i] = false;
            shape->meta.map[i+5] = true;
          }
        }
      }

      if (!doesIntersect &&
          shape->getPosition(lastTrueValid).y < x)
        shape->meta.appendY(10);

    }
  }
}

bool Tetris::currentWillBeOut(char direction){
  if (direction == 'L'){
    bool lowestSet = false;
    int lowest;

    for (int i = 0; i < 25; i++){
      if (current->meta.map[i] && !lowestSet){
        lowest = i;
        lowestSet = true;
      }

      if (current->meta.map[i] && i%5 < lowest%5 && lowestSet){
        lowest = i;
      }
    }

    if (!lowestSet)
      return false;

    if (current->getPosition(lowest).x - 10 < 0)
      return true;
  }

  if (direction == 'R'){
    bool highestSet = false;
    int highest;

    for (int i = 0; i < 25; i++){
      if (current->meta.map[i] && !highestSet){
        highest = i;
        highestSet = true;
      }

      if (current->meta.map[i] && i%5 > highest%5 && highestSet){
        highest = i;
      }
    }

    if (!highestSet)
      return false;

    if (current->getPosition(highest).x + 10 > 90)
      return true;
  }

  return false;
}

void Tetris::start(){
  spawnShape();

  while (!WindowShouldClose()){
    BeginDrawing();
    ClearBackground(BLACK);
    display.drawShape();
    EndDrawing();

    deltaTime = GetTime() - lastTime;
    lastTime = GetTime();

    if (hasPassedYAxis() || hasCollided()){
      correctPosition();
      if (hasPassedYAxis() || hasCollided()) spawnShape();
    }

    updateGlobalMap();

    if (IsKeyPressed(KEY_A) + IsKeyPressed(KEY_D) + IsKeyPressed(KEY_S) < 2){
      if (IsKeyPressed(KEY_W) && currentCanRotate()) rotate();

      if (IsKeyPressed(KEY_A) &&
          !currentWillCollideX(-10) &&
          !currentWillBeOut('L'))
        moveLeft();

      if (IsKeyPressed(KEY_D) &&
          !currentWillCollideX(10) &&
          !currentWillBeOut('R'))
        moveRight();

      if (IsKeyPressed(KEY_S)) moveDown();
    }

    deltaMoveDown();

    std::vector<int> fullLines = getFullLines();
    purgeFullLines(fullLines);
    correctLines(fullLines);

  }

  display.closeScreen();
}
