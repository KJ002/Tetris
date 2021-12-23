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
  dynamicProfileRef->push_back(shape);
}

void Display::removeShape(Object* shape){
  for (size_t i = 0; i < dynamicProfileRef->size(); i++){
    if (dynamicProfileRef->at(i) == shape){
      dynamicProfileRef->erase(dynamicProfileRef->begin()+i);
      return;
    }
  }
}

void Display::attachShape(Object shape){
  staticProfileRef->push_back(shape);
}

void Display::drawShape(){
  std::vector<Object> workingObjects;

  for (Object* i : *dynamicProfileRef)
    workingObjects.push_back(*i);

  for (int i = 0; i < staticProfileRef->size(); i++)
    workingObjects.push_back(staticProfileRef->at(i));

  for (int i = 0; i < workingObjects.size(); i++)
    workingObjects.at(i).draw();
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
