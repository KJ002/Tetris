#pragma once
#include "object.hpp"
#include <vector>
#include <raylib.h>
#include <map>


class Display{
private:
  int screenWidth, screenHeight;
  std::string profile;

  std::vector<Object*>* profileRef = nullptr;

  std::map<std::string, std::vector<Object*>> profiles;

public:
  Display(int width, int height, const char* title, int fps, std::string profile = "main");
  void switchProfile(std::string profile);
  std::string getProfile() {return this->profile;};

  void attachShape(Object* shape);
  void removeShape(Object* shape);

  void clear();

  void drawShape();
  void closeScreen() const;

  std::vector<Object*> exposeShapes(std::string profile) const;
};
