#pragma once
#include "object.hpp"
#include <vector>
#include <raylib.h>


class Display{
private:
  std::vector<Object*> shapes;
  int screenWidth, screenHeight;

  Vector2 WtoS(Vector2);

public:
  Display(int width, int height, const char* title, int fps);
  void attachShape(Object*);
  void removeShape(Object*);
  void drawShape() const;
  void closeScreen() const;

};
