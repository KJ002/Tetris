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
  Color colour = BLUE;

  Square(int x, int y, int width, int height, Color colour);
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

class Button{
private:
  int* x = &contents.x;
  int* y = &contents.y;

public:
  Button(std::string text,
         Vec2 pos,
         int fontSize,
         Color colour,
         int widthOffset = 0,
         int heightOffset = 0,
         Color bg = BLACK);

  int widthOffset = 0;
  int heightOffset = 0;

  Text contents = Text("", Vec2(0.f, 0.f), 0, RAYWHITE);
  Square box = Square(0, 0, 0, 0, RAYWHITE);

  Color bg_colour = {255, 255, 255, 255};

  int getX() const {return *x-(widthOffset)/2;};
  int getY() const {return *y-(heightOffset)/2;};

  int getWidth() const;
  int getHeight() const {return contents.fontSize+heightOffset;};

  bool isClicked() const;
};
