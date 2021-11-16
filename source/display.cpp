#include "display.hpp"
#include "object.hpp"
#include <raylib.h>


Display::Display(
    int screenWidth,
    int screenHeight,
    const char * title,
    int targetFPS
){
  InitWindow(screenWidth, screenHeight, title);
  SetTargetFPS(targetFPS);

  this->screenWidth = screenWidth;
  this->screenHeight = screenHeight;
}


void Display::attachShape(Object* shape){
  shapes.push_back(shape);
}

void Display::removeShape(Object * shape){
  for (size_t i = 0; i < shapes.size(); i++){
    if (shapes[i] == shape){
      shapes.erase(shapes.begin()+i);
    }
  }
}



void Display::drawShape() const{
  for (auto i : shapes)
    i->draw();
}

void Display::closeScreen() const{
  CloseWindow();
}
