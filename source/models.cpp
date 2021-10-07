#include "models.hpp"
#include <array>


TetrisMeta::TetrisMeta(int x, int y, int shape){
  this->x = x;
  this->y = y;

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
