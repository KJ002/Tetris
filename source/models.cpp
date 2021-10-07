#include "models.hpp"
#include <array>


TetrisMeta::TetrisMeta(int x, int y, int shape){
  origin = (Vec2){(float)x, (float)y};

  if (!shape){
    map = {
      0, 0, 0, 0, 0,
      0, 0, 0, 1, 0,
      0, 0, 0, 1, 0,
      0, 0, 0, 1, 0,
      0, 0, 0, 1, 0,
    };

    rotationalOrigin = (Vec2){2.5, 1.5};
  }
}

TetrisMeta::TetrisMeta(){
  TetrisMeta(0, 0, 0);
}

int TetrisMeta::getX() const{
  return origin.x;
}

int TetrisMeta::getY() const{
  return origin.y;
}

void TetrisMeta::setX(const int x){
  origin.x = (float)x;
}

void TetrisMeta::setY(const int y){
  origin.y = (float)y;
}
