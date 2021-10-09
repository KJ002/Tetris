#pragma once
#include <array>
#include "vec2.hpp"


struct TetrisMeta{
  std::array<bool, 25> map;
  Vec2 origin;
  Vec2 rotationalOrigin;

  int getX() const;
  int getY() const;

  void setX(const int x);
  void setY(const int y);

  int appendX(const int x);
  int appendY(const int y);

  TetrisMeta(int x, int y, int shape);
  TetrisMeta();
};
