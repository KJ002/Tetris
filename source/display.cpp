#include "display.hpp"
#include "object.hpp"
#include <raylib.h>

#define shapes this->profiles[this->profile]

Display::Display(
    int screenWidth,
    int screenHeight,
    const char * title,
    int targetFPS,
    std::string profile
){
  InitWindow(screenWidth, screenHeight, title);
  SetTargetFPS(targetFPS);

  this->profile = profile;
  this->screenWidth = screenWidth;
  this->screenHeight = screenHeight;
}

void Display::switchProfile(std::string profile){
  if (!profiles.contains(profile))
    shapes = {};

  this->profile = profile;
}

void Display::attachShape(Object* shape){
  shapes.push_back(shape);
}

void Display::removeShape(Object* shape){
  for (size_t i = 0; i < shapes.size(); i++){
    if (shapes[i] == shape){
      shapes.erase(shapes.begin()+i);
    }
  }
}

void Display::drawShape(){
  for (Object* i : shapes)
    i->draw();
}

void Display::closeScreen() const{
  CloseWindow();
}

void Display::clear(){
  shapes.clear();
}

std::vector<Object*> Display::exposeShapes(){
  return shapes;
}
