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
  if (!dynamicProfiles.contains(profile))
    dynamicProfiles[profile] = {};

  if (!staticProfiles.contains(profile))
    staticProfiles[profile] = {};

  this->profile = profile;

  this->dynamicProfileRef = &dynamicProfiles[profile];
  this->staticProfileRef = &staticProfiles[profile];
}

void Display::attachShape(Object* shape){
  profileRef->push_back(shape);
}

void Display::removeShape(Object* shape){
  for (size_t i = 0; i < profileRef->size(); i++){
    if (profileRef->at(i) == shape)
      profileRef->erase(profileRef->begin()+i);
  }
}

void Display::drawShape(){
  for (Object* i : *profileRef)
    i->draw();
}

void Display::closeScreen() const{
  CloseWindow();
}

void Display::clear(){
  profileRef->clear();
}

std::vector<Object*> Display::exposeShapes(std::string profile) const{
  return profiles.at(profile);
}
