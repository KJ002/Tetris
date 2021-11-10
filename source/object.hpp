#pragma once
#include "models.hpp"
#include "vec2.hpp"
#include <raylib.h>

struct Object{
  virtual void draw() const = 0;
  virtual ~Object(){}
};

struct Square : public Object{
  int x = 0;
  int y = 0;
  int width = 0;
  int height = 0;

  Square(int x, int y, int width, int height);
  void draw() const override;
};

struct TetrisBlock : public Object{
  bool active = true;
  TetrisMeta meta;

  TetrisBlock(int x, int y, int shape);
  bool colliding(TetrisBlock* other);
  void draw() const override;
  void rotateLeft();
  void rotateRight();
  Vec2 getPosition(int x);
};

struct Text : public Object{
  char * text;

  int x = 0;
  int y = 0;

  int fontSize = 10;
  Color colour;

  Text(char * text = (char*)"", int x = 0, int y = 0, int fontSize = 0, Color colour = BLACK);
  Text(char * text = (char*)"", Vec2 pos = Vec2(0, 0), int fonstSize = 0, Color colour = BLACK);
  void draw() const override;

};
