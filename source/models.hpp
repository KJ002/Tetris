#pragma once
#include <array>


struct TetrisMeta{
  std::array<bool, 25> map;
  int x;
  int y;

  TetrisMeta(int x, int y, int shape);
  TetrisMeta();
};
