#include "models.hpp"
#include <array>


TetrisMeta::TetrisMeta(int x, int y, int shape){
  origin = (Vec2){(float)x, (float)y};

  if (!shape){
    map = {
      0, 0, 0, 0, 0,
      0, 0, 1, 0, 0,
      0, 0, 1, 0, 0,
      0, 0, 1, 0, 0,
      0, 0, 1, 0, 0,
    };

    rotationalOrigin = (Vec2){2.5, 1.5};
  }

  if (shape == 1){
     map = {
      0, 0, 0, 0, 0,
      0, 0, 0, 0, 0,
      0, 0, 1, 0, 0,
      0, 0, 1, 0, 0,
      0, 1, 1, 0, 0,
    };

    rotationalOrigin = (Vec2){2, 1};
  }

  if (shape == 2){
     map = {
      0, 0, 0, 0, 0,
      0, 0, 0, 0, 0,
      0, 1, 0, 0, 0,
      0, 1, 0, 0, 0,
      0, 1, 1, 0, 0,
    };

    rotationalOrigin = (Vec2){1, 1};
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

void TetrisMeta::setX(const float x){
  origin.x = x;
}

void TetrisMeta::setY(const float y){
  origin.y = y;
}

void TetrisMeta::set(const Vec2 v){
  origin = v;
}

int TetrisMeta::appendX(const int x){
  origin.x += x;
  return origin.x;
}

int TetrisMeta::appendY(const int y){
  origin.y += y;
  return origin.y;
}

Vec2 TetrisMeta::append(const Vec2 v){
  origin = origin + v;

  return origin;
}
