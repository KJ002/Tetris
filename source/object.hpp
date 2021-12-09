#pragma once
#include "models.hpp"
#include "vec2.hpp"
#include <string>
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
  std::string text;

  int x;
  int y;

  int fontSize;
  Color colour;

  Text(std::string text, Vec2 pos, int fonstSize, Color colour = BLACK);
  void draw() const override;
};

struct Button : public Object{
  Text contents;

  int* x = &contents.x;
  int* y = &contents.y;

  Color bg_colour = {255, 255, 255, 255};

  void getX() const;
  void getY() const;

  void draw() const override;
  bool is_clicked() const;
};
