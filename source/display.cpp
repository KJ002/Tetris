#include "display.hpp"
#include "object.hpp"
#include <raylib.h>


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
    profiles[profile] = {};

  this->profile = profile;
}

void Display::attachShape(Object* shape){
  profiles[profile].push_back(shape);
}

void Display::removeShape(Object* shape){
  for (size_t i = 0; i < profiles[profile].size(); i++){
    if (profiles[profile][i] == shape){
      profiles[profile].erase(profiles[profile].begin()+i);
    }
  }
}

void Display::drawShape(){
  for (Object* i : profiles[profile])
    i->draw();
}

void Display::closeScreen() const{
  CloseWindow();
}

void Display::clear(){
  profiles[profile].clear();
}

std::vector<Object*> Display::exposeShapes(){
  return this->profiles[profile];
}
