#pragma once
#include <array>
#include "vec2.hpp"


struct TetrisMeta{
  std::array<bool, 25> map;
  Vec2 origin;
  Vec2 rotationalOrigin;

  int getY();
  int getX();

  TetrisMeta(int x, int y, int shape);
  TetrisMeta();
};
