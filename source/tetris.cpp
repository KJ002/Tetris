#include "tetris.hpp"
#include "models.hpp"
#include "object.hpp"
#include <raylib.h>
#include <algorithm>
#include <string>
#include <vector>
#include <cstdlib>

#include <iostream>

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

  display.attachShape(&scoreObj);
}

void Tetris::spawnShape(){
  /*
  ** When current has collided create a new shape
  ** and allocate a pointer to it onto the heap and
  ** push current into shapes.
   */

  shapes.push_back(current);

  TetrisBlock * x = new TetrisBlock(spawnPosition.x, spawnPosition.y, rand());

  // Correct current position spawn to top of current

  int bottom;

  for (int i = 24; i >= 0; i--){
    if (x->meta.map[i]){
      bottom = i;
      break;
    }
  }

  x->meta.appendY(-(x->getPosition(bottom).y));

  // Clean up previous current values

  currentBlockBuffer = 0;
  current = x;
  display.attachShape(x);
}

void Tetris::moveDown(){
  /*
  ** Alias to move current down.
   */

  current->meta.appendY(10);
}

void Tetris::moveLeft(){
  /*
  ** Alias to move current left.
   */

  current->meta.appendX(-10);
}

void Tetris::moveRight(){
  /*
  ** Alias to move current right.
   */

  current->meta.appendX(10);
}

void Tetris::deltaMoveDown(){
  /*
  ** Appends the displacement of time multiplied
  ** by the speed to currentBlockBuffer and when
  ** it is greater that 10 move current down 10
  ** and subtract 10 from currentBlockBuffer.
   */

  currentBlockBuffer += 10*((debug) ? .01667 : deltaTime);

  if (currentBlockBuffer >= 10){
    moveDown();
    currentBlockBuffer-=10;
  }
}

void Tetris::rotate(){
  /*
  ** Alias to rotate current
   */

  current->rotateRight();
}

void Tetris::correctPosition(){
  /*
  ** If current were about to collide with another
  ** shape this function gives the user time to
  ** fine tune the poition
   */

  double time = GetTime();

  while (time+1 > GetTime()){
    if (IsKeyPressed(KEY_A) + IsKeyPressed(KEY_D) < 2){
      if (IsKeyPressed(KEY_A) &&
          !currentWillCollide(Vec2(-10, 0)) &&
          !currentWillBeOut('L'))
        moveLeft();

      if (IsKeyPressed(KEY_D) &&
          !currentWillCollide(Vec2(10, 0)) &&
          !currentWillBeOut('R'))
        moveRight();
    }

    if (IsKeyPressed(KEY_S))
      break;

    BeginDrawing();
    ClearBackground(BLACK);
    display.drawShape();
    EndDrawing();

  }
}

bool Tetris::hasPassedYAxis(){
  /*
  ** Checks if current has passed the y-axis
   */

  int i = 25;
  bool foundLowestIndex = false;

  while (i && !foundLowestIndex){
    i--;
    foundLowestIndex = current->meta.map[i];
  }

  return current->getPosition(i).y+10 >= GetScreenHeight();
}

void Tetris::cleanGlobalMap(){
  /*
  ** Cleans the global map.
   */

  for (int i = 0; i < 200; i++)
    globalMap[i] = 0;
}

int Tetris::posToIndex(int x, int y){
  /* Correct data
  ** x and y must ALWAYS be a multiple
  ** of 10 for this to work but due to the
  ** nature of tetris this should be fine.
   */

  x = x/10;
  y = y/10;

  // Calculate index position

  return (y*10)+x;
}

int Tetris::posToIndex(Vec2 v){
  /* Correct data
  ** v.x and v.y must ALWAYS be a multiple
  ** of 10 for this to work but due to the
  ** nature of tetris this should be fine.
  */

  v.x = v.x/10;
  v.y = v.y/10;

  // Calculate index position

  return (v.y*10)+v.x;
}

bool Tetris::currentWillCollide(Vec2 direction){
  /*
  ** Detects if current will intersect another block
  ** given a position offset in the form of a Vec2.
   */

  TetrisBlock future = *current;

  future.meta.append(direction);

  for (TetrisBlock* other : shapes){
    if (other != current && future.colliding(other)) return true;
  }

  return false;

}

bool Tetris::currentCanRotate(){
  /*
  ** Checks if current can rotate 90 degrees
  ** clockwise without going out of bounds.
   */

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
  /*
  ** Creates a "global map" of the Tetris board.
  ** The global map is an array of indexs with a
  ** true state if that index is occupied by a
  ** tetris piece.
   */

  cleanGlobalMap();

  for (TetrisBlock* object : shapes){
    if (object != current){
      for (int i = 0; i < 25; i++){
        if (object->meta.map[i]){

          Vec2 pos = object->getPosition(i);

          if (pos.x >= 0 && pos.x < 100 && pos.y >= 0 && pos.y < 200){
            int index = posToIndex(pos);

            globalMap[index] = 1;
          }
        }
      }
    }
  }
}

std::vector<int> Tetris::getFullLines(){
  /*
  ** Gets all full lines of the Tetris board.
  ** The functionality of Tetris blocks
  ** outside of the board is undefined.
   */

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
  /*
  ** Deletes all valid indexs on a Tetris block map
  ** provided the points of intersection.
   */

  for (TetrisBlock* x : shapes){
    for (int i = 0; i < 25; i++){
      if (std::find(y.begin(), y.end(), x->getPosition(i).y) != y.end()){
        x->meta.map[i] = false;
      }
    }
  }
}

void Tetris::correctLines(std::vector<int> y){
  /*
  ** Corrects all positions of shapes by y += 10.
  ** However this function has to account for the
  ** deletion of a row upon the completeion of a
  ** line and therefor it has to handle shapes with
  ** an intersection and without an intersection
  ** differently.
  **
  ** Shapes with an intersection have to have
  ** all valid indexes on the map above the
  ** position of intersection to be moved down
  ** by 10. This is handled by mutating the map.
  **
  ** Shapes that do not have an intersection but
  ** are above the point of intersection and moved
  ** down by 10 on the y-axis.
  **
  ** All other shapes are left untouched.
   */

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

void Tetris::updateScore(std::vector<int> y){
  /*
  ** Update score class attribute based on the
  ** ammount of full lines found.
   */

  // Update score based on intersections
  score += 100*y.size();

  // Format score into a string and pass to scoreObj.text
  scoreObj.text = std::to_string(score);

  // Adjust score position due to length change
  updateScorePosition();
}

void Tetris::updateScorePosition(){
  /*
  ** Correct scoreObj x position to align by the right opposed to the left
   */

  int textSize = MeasureText(scoreObj.text.data(), scoreObj.fontSize);
  int delta = scoreObjNEPos.x - (scoreObj.x + textSize);

  scoreObj.x += delta;
}

bool Tetris::currentWillBeOut(char direction){
  /*
  ** Detects if the current shape will
  ** be out of bounds if Left or Right
  ** keys were to be pressed.
   */

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

bool Tetris::shouldGameOver(){
  for (int i = 0; i < 10; i++){
    if (globalMap[i])
      return true;
  }

  return false;
}

void Tetris::clearBoard(){
  score = 0;

  display.clear();
  shapes.clear();

  display.attachShape(current);
  display.attachShape(&scoreObj);
}

void Tetris::start(){
  /*
  ** Tetris game main loop. All delta time,
  ** key presses, logic and rendering is
  ** done here.
   */

  spawnShape();

  while (!WindowShouldClose()){
    BeginDrawing();
    ClearBackground(BLACK);
    display.drawShape();
    EndDrawing();

    updateGlobalMap();

    if (shouldGameOver())
      clearBoard();

    deltaTime = GetTime() - lastTime;
    lastTime = GetTime();

    if (hasPassedYAxis() || currentWillCollide(Vec2(0, 10))){
      correctPosition();
      if (hasPassedYAxis() || currentWillCollide(Vec2(0, 10))){
        spawnShape();
        continue;
      }
    }


    deltaMoveDown();

    if (IsKeyPressed(KEY_A) + IsKeyPressed(KEY_D) + IsKeyPressed(KEY_S) < 2){
      if (IsKeyPressed(KEY_W) && currentCanRotate()) rotate();

      if (IsKeyPressed(KEY_A) &&
          !currentWillCollide(Vec2(-10, 0)) &&
          !currentWillBeOut('L'))
        moveLeft();

      if (IsKeyPressed(KEY_D) &&
          !currentWillCollide(Vec2(10, 0)) &&
          !currentWillBeOut('R'))
        moveRight();

      if (IsKeyPressed(KEY_S)) moveDown();
    }

    std::vector<int> fullLines = getFullLines();
    purgeFullLines(fullLines);
    correctLines(fullLines);
    updateScore(fullLines);

  }

  display.closeScreen();
}
