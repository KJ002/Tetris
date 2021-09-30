#include <raylib.h>
#include <vector>
#include "object.hpp"
#include <iostream>

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
