#pragma once

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

struct TetrisBlock{
  int x = 0;
  int y = 0;

  TetrisBlock(int x, int y, int shape);
  void draw() const override;
};
