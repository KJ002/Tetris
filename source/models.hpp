#pragma once
#include <array>
#include <raylib.h>
#include "vec2.hpp"

struct TetrisMeta{
  std::array<bool, 25> map;
  Vec2 origin;
  Vec2 rotationalOrigin;
  Color colour;
  bool outlines = false;

  int getX() const;
  int getY() const;

  Vec2 get() const;

  Rectangle getRec() const;

  void setX(const int x);
  void setY(const int y);

  void setX(const float x);
  void setY(const float y);

  void set(const Vec2 v);

  int appendX(const int x);
  int appendY(const int y);

  float appendX(const float x);
  float appendY(const float y);

  Vec2 append(const Vec2 v);

  TetrisMeta(int x, int y, int shape);
  TetrisMeta();
};
