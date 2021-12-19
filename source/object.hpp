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
  Vec2 pos;
  Vec2 size;

  int textWidth(){return MeasureText(contents.text.data(), contents.fontSize);};

public:
  Button(
    std::string text,
    Vec2 pos,
    Vec2 size,
    int fontSize,
    Color foreground = RAYWHITE,
    Color background = BLACK
  );

  Text contents;
  Square box;

  void setPos(Vec2 newPos);

  bool isClicked() const;
  void update();
};
