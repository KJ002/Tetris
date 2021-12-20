#include "tetris.hpp"
#include "models.hpp"
#include "object.hpp"
#include <raylib.h>
#include <algorithm>
#include <string>
#include <vector>
#include <cstdlib>

#include <iostream>

#define scoreStart 20

Tetris::Tetris(
  Display* display,
  bool debug)
{
  this->display = display;
  this->debug = debug;

  cleanGlobalMap();
  display->attachShape(scoreObj);

  // Initial setup phase

  spawnShape();
  updateFutureCurrent();

  display->attachShape(&currentFuture);
}

void Tetris::spawnShape(){
  /*
  ** When current has collided create a new shape
  ** and allocate a pointer to it onto the heap and
  ** push current into shapes.
   */

  if (current != NULL)
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
  display->attachShape(x);
}

void Tetris::moveDown(TetrisBlock* block){
  /*
  ** Alias to move block down.
   */

  block->meta.appendY(10);
}

void Tetris::moveLeft(TetrisBlock* block){
  /*
  ** Alias to move current left.
   */

  block->meta.appendX(-10);
}

void Tetris::moveRight(TetrisBlock* block){
  /*
  ** Alias to move current right.
   */

  block->meta.appendX(10);
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
    moveDown(current);
    currentBlockBuffer-=10;
  }
}

void Tetris::rotate(TetrisBlock* block){
  /*
  ** Alias to rotate current
   */

  block->rotateRight();
}

void Tetris::correctPosition(){
  /*
  ** If current were about to collide with another
  ** shape this function gives the user time to
  ** fine tune the poition
   */

  double time = GetTime();

  display->removeShape(&currentFuture);

  while (time+.4 > GetTime()){
    BeginDrawing();
    ClearBackground(BLACK);
    display->drawShape();
    EndDrawing();

    if (IsKeyPressed(KEY_A) + IsKeyPressed(KEY_D) < 2){
      if (IsKeyPressed(KEY_A) &&
          !willCollide(current, Vec2(-10, 0)) &&
          !willBeOut(current, 'L'))
        moveLeft(current);

      if (IsKeyPressed(KEY_D) &&
          !willCollide(current, Vec2(10, 0)) &&
          !willBeOut(current, 'R'))
        moveRight(current);
    }

    if (IsKeyPressed(KEY_S))
      break;
  }

  display->attachShape(&currentFuture);
}

void Tetris::autoplace(TetrisBlock* block){
  while (!isCollideYAxis(block) && !willCollide(block, Vec2(0, 10)))
    moveDown(block);
}

bool Tetris::isCollideYAxis(TetrisBlock* block){
  /*
  ** Checks if current has passed the y-axis
   */

  int i = 25;
  bool foundLowestIndex = false;

  while (i && !foundLowestIndex){
    i--;
    foundLowestIndex = block->meta.map[i];
  }

  return block->getPosition(i).y+10 >= GetScreenHeight();
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

bool Tetris::willCollide(TetrisBlock* block, Vec2 direction){
  /*
  ** Detects if current will intersect another block
  ** given a position offset in the form of a Vec2.
   */

  TetrisBlock future = *block;

  future.meta.append(direction);

  for (TetrisBlock* other : shapes){
    if (other != block && future.colliding(other)) return true;
  }

  return false;

}

bool Tetris::canRotate(TetrisBlock* block){
  /*
  ** Checks if current can rotate 90 degrees
  ** clockwise without going out of bounds.
   */

  TetrisBlock future = *block;

  future.rotateRight();

  for (TetrisBlock* other : shapes){
    if (other != block && future.colliding(other)) return false;
  }

  for (int i = 0; i < 25; i++){
    if(future.meta.map[i] &&
       (future.getPosition(i).x < 0 ||
        future.getPosition(i).x >= 100 ||
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

void Tetris::getFullLines(){
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

  fullLines = result;
}

void Tetris::purgeFullLines(){
  /*
  ** Deletes all valid indexs on a Tetris block map
  ** provided the points of intersection.
   */

  for (TetrisBlock* x : shapes){
    for (int i = 0; i < 25; i++){
      if (std::find(fullLines.begin(), fullLines.end(), x->getPosition(i).y) != fullLines.end()){
        x->meta.map[i] = false;
      }
    }
  }
}

void Tetris::correctLines(){
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

  for (int x : fullLines){
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

void Tetris::updateScore(){
  /*
  ** Update score class attribute based on the
  ** ammount of full lines found.
   */

  // Update score based on intersections
  score += 100*fullLines.size();

  // Format score into a string and pass to scoreObj.text
  scoreObj->text = std::to_string(score);

  // Adjust score position due to length change
  updateScorePosition();
}

void Tetris::updateScorePosition(){
  /*
  ** Correct scoreObj x position to align by the right opposed to the left
   */

  int textSize = MeasureText(scoreObj->text.data(), scoreObj->fontSize);
  int delta = scoreObjNEPos.x - (scoreObj->x + textSize);

  scoreObj->x += delta;
}

bool Tetris::willBeOut(TetrisBlock* block, char direction){
  /*
  ** Detects if the current shape will
  ** be out of bounds if Left or Right
  ** keys were to be pressed.
   */

  if (direction == 'L'){
    bool lowestSet = false;
    int lowest;

    for (int i = 0; i < 25; i++){
      if (block->meta.map[i] && !lowestSet){
        lowest = i;
        lowestSet = true;
      }

      if (block->meta.map[i] && i%5 < lowest%5 && lowestSet){
        lowest = i;
      }
    }

    if (!lowestSet)
      return false;

    if (block->getPosition(lowest).x - 10 < 0)
      return true;
  }

  if (direction == 'R'){
    bool highestSet = false;
    int highest;

    for (int i = 0; i < 25; i++){
      if (block->meta.map[i] && !highestSet){
        highest = i;
        highestSet = true;
      }

      if (block->meta.map[i] && i%5 > highest%5 && highestSet){
        highest = i;
      }
    }

    if (!highestSet)
      return false;

    if (block->getPosition(highest).x + 10 > 90)
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
  updateScores();

  for (auto shape : shapes)
    delete shape;

  // Empty display and shape vectors

  display->clear();
  shapes.clear();

  // Re-attach all shapes

  display->attachShape(current);
  display->attachShape(scoreObj);

  for (Text* x : pastScores)
    display->attachShape(x);
}

void Tetris::updateScores(){
  scoreObj->y = scoreStart + ((int)pastScores.size() * 10);
  pastScores.push_back(scoreObj);

  scoreObj = new Text("0", scoreObjNEPos, 10, RAYWHITE);
}

void Tetris::updateFutureCurrent(){
  currentFuture = *current;
  currentFuture.meta.outlines = true;
  currentFuture.meta.colour.a = 100;
  autoplace(&currentFuture);
}

void Tetris::update(){
  /*
  ** Tetris game main loop. All delta time,
  ** key presses, logic and rendering is
  ** done here.
   */

  updateGlobalMap();

  if (shouldGameOver())
    clearBoard();

  if (lastTime == -1)
    lastTime = GetTime();

  deltaTime = GetTime() - lastTime;
  lastTime = GetTime();

  if (isCollideYAxis(current) || willCollide(current, Vec2(0, 10))){
    correctPosition();
    if (isCollideYAxis(current) || willCollide(current, Vec2(0, 10))){
      spawnShape();
      return;
    }
  }

  deltaMoveDown();

  updateFutureCurrent();

  if (IsKeyPressed(KEY_A) + IsKeyPressed(KEY_D) + IsKeyPressed(KEY_S) < 2){
    if (IsKeyPressed(KEY_W) && canRotate(current)) rotate(current);

    if (IsKeyPressed(KEY_A) &&
        !willCollide(current, Vec2(-10, 0)) &&
        !willBeOut(current, 'L'))
      moveLeft(current);

    if (IsKeyPressed(KEY_D) &&
        !willCollide(current, Vec2(10, 0)) &&
        !willBeOut(current, 'R'))
      moveRight(current);

    if (IsKeyPressed(KEY_S)) moveDown(current);
  }

  if (IsKeyPressed(KEY_SPACE))
    autoplace(current);

  if (IsKeyPressed(KEY_ESCAPE))
    display->switchProfile("menu");

  getFullLines();
  purgeFullLines();
  correctLines();
  updateScore();
  fullLines.clear();
}
