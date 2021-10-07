#include "models.hpp"
#include <array>


TetrisMeta::TetrisMeta(int x, int y, int shape){
  origin = (Vec2){(float)x, (float)y};

  if (!shape)
    map = {
      0, 0, 0, 0, 0,
      0, 0, 0, 1, 0,
      0, 0, 0, 1, 0,
      0, 0, 0, 1, 0,
      0, 0, 0, 1, 0,
    };
}

TetrisMeta::TetrisMeta(){
  TetrisMeta(0, 0, 0);
}

int TetrisMeta::getX(){
  return origin.x;
}

int TetrisMeta::getY(){
  return origin.y;
}
