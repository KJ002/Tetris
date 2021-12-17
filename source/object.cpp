#include <raylib.h>
#include <vector>
#include <iostream>

#include "object.hpp"
#include "utils.hpp"
#include "models.hpp"
#include "vec2.hpp"

#define LOG(x) std::cout << x << std::endl

struct Point{
  int x;
  int y;
};

extern "C" Point getCoords(int value, int divisor);

Square::Square(int x, int y, int width, int height, Color colour){
  this->x = x;
  this->y = y;
  this->width = width;
  this->height = height;
  this->colour = colour;
}

void Square::draw() const{
  DrawRectangle(x, y, width, height, BLUE);
}

TetrisBlock::TetrisBlock(int x, int y, int shape){
  this->meta = {x, y, shape};
}

void TetrisBlock::draw() const{

  for (int i = 0; i < 25; i++){
    if (meta.map[i]){

      Point delta = getCoords(i, 5);

      if (!meta.outlines)
        DrawRectangle(
          meta.getX()+(delta.x*10),
          meta.getY()+(delta.y*10),
          10,
          10,
          meta.colour
        );

      else{

        Rectangle block = meta.getRec();

        block.x+=delta.x*10;
        block.y+=delta.y*10;

        block.width *= meta.blockScale;
        block.height *= meta.blockScale;

        Vec2 d(10-block.width, 10-block.height);

        block.x+=d.x/2;
        block.y+=d.y/2;

        DrawRectangleLinesEx(
          block,
          1,
          meta.colour
        );
      }
    }
  }
}

bool TetrisBlock::colliding(TetrisBlock *other){

  for (int i = 0; i < 25; i++){
    if (meta.map[i])
      for (int i2 = 0; i2 < 25; i2++){
        if (other->meta.map[i2] && getPosition(i) == other->getPosition(i2)){
          return true;
        }
      }
  }

  return false;
}

void TetrisBlock::rotateLeft(){
  std::array<bool, 25> tempMap = {};
  for (int i = 0; i < 25; i++){
    if(meta.map[i]){
      meta.map[i] = 0;

      Vec2 mapRelative(i%5, 4-((int)i/5));

      Vec2 result = mapRelative.rotate(90, meta.rotationalOrigin);

      int position = 0;
      int deltaY;

      deltaY = 5-result.y;
      deltaY--;

      if (deltaY > 0){
        position += 5*deltaY;
        position += result.x;
      }

      else{
        position = result.x;
      }

      tempMap[position] = 1;

    }
  }

  meta.map = tempMap;
}

void TetrisBlock::rotateRight(){
  std::array<bool, 25> tempMap = {};
  for (int i = 0; i < 25; i++){
    if(meta.map[i]){
      meta.map[i] = 0;

      Vec2 mapRelative(i%5, 4-((int)i/5));

      Vec2 result = mapRelative.rotate(270, meta.rotationalOrigin);

      int position = 0;
      int deltaY;

      deltaY = 5-result.y;
      deltaY--;

      if (deltaY > 0){
        position += 5*deltaY;
        position += result.x;
      }

      else{
        position = result.x;
      }

      tempMap[position] = 1;

    }
  }

  meta.map = tempMap;
}

Vec2 TetrisBlock::getPosition(int x){
  Vec2 result = meta.get();

  result.x += (x%5)*10;
  result.y += intDiv(x, 5)*10;

  return result;
}

Text::Text(
  std::string _text,
  Vec2 _pos,
  int _fontSize,
  Color _colour
):
  text(_text),
  x(_pos.x),
  y(_pos.y),
  fontSize(_fontSize),
  colour(_colour)
{}

void Text::draw() const{
  DrawText(text.data(), x, y, fontSize, colour);
}

Button::Button(
  std::string text,
  Vec2 pos,
  int fontSize,
  Color colour,
  int widthOffset,
  int heightOffset,
  Color bg_colour
)
{
  this->widthOffset = widthOffset;
  this->heightOffset = heightOffset;
  this->bg_colour = bg_colour;

  this->contents = Text(text, pos, fontSize, colour);
  this->box = Square(getX(), getY(), getWidth(), getHeight(), bg_colour);
}

int Button::getWidth() const{
  return MeasureText(contents.text.data(), contents.fontSize) + widthOffset;
}

bool Button::isClicked() const{
  if (IsMouseButtonPressed(1)){
    if (GetMouseX() >= getX() && GetMouseX() <= getX()+getWidth())
      if (GetMouseY() >= getY() && GetMouseY() <= getY()+getHeight())
        return true;
  }

  return false;
}
