#include <raylib.h>
#include <vector>
#include <iostream>

#include "object.hpp"
#include "utils.hpp"
#include "models.hpp"
#include "vec2.hpp"

#define LOG(x) std::cout << x << std::endl

Square::Square(int x, int y, int width, int height){
  this->x = x;
  this->y = y;
  this->width = width;
  this->height = height;
}

void Square::draw() const{
  DrawRectangle(x, y, width, height, BLUE);
}

TetrisBlock::TetrisBlock(int x, int y, int shape){
  this->meta = {x, y, shape};
}

void TetrisBlock::draw() const{
  for (int i = 0; i < 25; i++){
    if (meta.map[i]){
      int deltaX = i%5;
      int deltaY = (int)i/5;

      DrawRectangle(
        meta.getX()+(deltaX*10),
        meta.getY()+(deltaY*10),
        10,
        10,
        BLUE
      );

    }
  }
}

bool TetrisBlock::colliding(TetrisBlock *other){

  // Filter out "collide surfaces"

  for (int i = 0; i < 25; i++){
    if (meta.map[i] &&
        !(safeGet<bool, 25>(i+5, meta.map))){
      for (int i2 = 0; i2 < 25; i2++){
        if (meta.map[i2]){

          // Check for overlap

          int thisX = getPosition(i+5).x;
          int thisY = getPosition(i+5).y;

          int otherX = other->getPosition(i2).x;
          int otherY = other->getPosition(i2).y;

          if (thisX == otherX && thisY == otherY)
            return true;
        }
      }
    }
  }

  return false;
}

void TetrisBlock::rotateLeft(){
  std::array<bool, 25> tempMap = {};
  for (int i = 0; i < 25; i++){
    if(meta.map[i]){
      meta.map[i] = 0;

      Vec2 mapRelative(i%5, 4-((int)i/5));

      Vec2 result = mapRelative.rotate(90, meta.rotationalOrigin);

      int position = 0;
      int deltaY;

      deltaY = 5-result.y;
      deltaY--;

      if (deltaY > 0){
        position += 5*deltaY;
        position += result.x;
      }

      else{
        position = result.x;
      }

      tempMap[position] = 1;

    }
  }

  meta.map = tempMap;
}

void TetrisBlock::rotateRight(){
  std::array<bool, 25> tempMap = {};
  for (int i = 0; i < 25; i++){
    if(meta.map[i]){
      meta.map[i] = 0;

      Vec2 mapRelative(i%5, 4-((int)i/5));

      Vec2 result = mapRelative.rotate(270, meta.rotationalOrigin);

      int position = 0;
      int deltaY;

      deltaY = 5-result.y;
      deltaY--;

      if (deltaY > 0){
        position += 5*deltaY;
        position += result.x;
      }

      else{
        position = result.x;
      }

      tempMap[position] = 1;

    }
  }

  meta.map = tempMap;
}

Vec2 TetrisBlock::getPosition(int x){
  Vec2 result = meta.get();
  result.x += (x%5)*10;
  result.y += intDiv(x, 5)*10;

  return result;
}
