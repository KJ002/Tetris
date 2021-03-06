#include "models.hpp"
#include <array>
#include <raylib.h>


TetrisMeta::TetrisMeta(int x, int y, int shape){
  shape = shape % 7;

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
    colour = BLUE;
  }

  if (shape == 1){
     map = {
      0, 0, 0, 0, 0,
      0, 0, 0, 0, 0,
      0, 1, 0, 0, 0,
      0, 1, 0, 0, 0,
      1, 1, 0, 0, 0,
    };

    rotationalOrigin = (Vec2){1, 1};
    colour = DARKBLUE;
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
    colour = GOLD;

  }

  if (shape == 3){
     map = {
      0, 0, 0, 0, 0,
      0, 0, 0, 0, 0,
      0, 1, 1, 0, 0,
      0, 1, 1, 0, 0,
      0, 0, 0, 0, 0,
    };

    rotationalOrigin = (Vec2){1.5, 1.5};
    colour = YELLOW;
  }

   if (shape == 4){
     map = {
      0, 0, 0, 0, 0,
      0, 0, 0, 0, 0,
      0, 1, 1, 0, 0,
      1, 1, 0, 0, 0,
      0, 0, 0, 0, 0,
    };

    rotationalOrigin = (Vec2){1, 1};
    colour = LIME;
  }

  if (shape == 5){
     map = {
      0, 0, 0, 0, 0,
      0, 0, 0, 0, 0,
      0, 1, 0, 0, 0,
      1, 1, 1, 0, 0,
      0, 0, 0, 0, 0,
    };

    rotationalOrigin = (Vec2){1, 1};
    colour = MAGENTA;
  }

  if (shape == 6){
     map = {
      0, 0, 0, 0, 0,
      0, 0, 0, 0, 0,
      1, 1, 0, 0, 0,
      0, 1, 1, 0, 0,
      0, 0, 0, 0, 0,
    };

    rotationalOrigin = (Vec2){1, 1};
    colour = RED;
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

Vec2 TetrisMeta::get() const{
  return origin;
}

Rectangle TetrisMeta::getRec() const{
  return (Rectangle){origin.x, origin.y, 10., 10.};
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

float TetrisMeta::appendX(const float x){
  origin.x += x;
  return origin.x;
}

float TetrisMeta::appendY(const float y){
  origin.y += y;
  return origin.y;
}

Vec2 TetrisMeta::append(const Vec2 v){
  origin = origin + v;

  return origin;
}
