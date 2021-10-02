#include <raylib.h>
#include <vector>
#include <iostream>

#include "object.hpp"
#include "utils.hpp"

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
  this->x = x;
  this->y = y;
}

void TetrisBlock::draw() const{
  for (int i = 0; i < 25; i++){
    if (shape[i]){
      int deltaX = i%5;
      int deltaY = (int)i/5;

      DrawRectangle(x+(deltaX*10), y+(deltaY*10), 10, 10, BLUE);

    }
  }
}

bool TetrisBlock::colliding(TetrisBlock *other){
  // Check if we are comparing two active blocks

  if (other->active)
    return true;

  // Filter out "collide surfaces"

  for (int i = 0; i < 25; i++){
    if (shape[i] && !(safeGet<bool>(i+5, shape, 25))){
      for (int i2 = 0; i2 < 25; i2++){
        if (other->shape[i2] && !(safeGet<bool>(i2-5, other->shape, 25))){

          // Check that if 10 (width and height of each block) they overlap

          int thisX = x+((i%5)*10);
          int thisY = y+(((int)i/5)*10);

          int otherX = other->x+((i2%5)*10);
          int otherY = other->y+(((int)i2/5)*10);

          if (thisX == otherX &&
              std::abs(thisY-otherY) == 10)
            return true;
        }
      }
    }
  }

  return false;
}
