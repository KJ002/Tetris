#pragma once
#include "object.hpp"
#include <vector>
#include <raylib.h>
#include <map>


class Display{
private:
  int screenWidth, screenHeight;
  std::string profile;

  std::vector<Object*>* dynamicProfileRef = nullptr;
  std::vector<Object>* staticProfileRef = nullptr;

  std::map<std::string, std::vector<Object*>> dynamicProfiles;
  std::map<std::string, std::vector<Object>> staticProfiles;

  Vector2 WtoS(Vector2);

public:
  Display(int width, int height, const char* title, int fps, std::string profile = "main");
  void switchProfile(std::string profile);
  std::string getProfile() {return this->profile;};

  void attachShape(Object* shape);
  void removeShape(Object* shape);

  void attachShape(Object shape);
  void removeShape(Object shape);

  void clearDynamic();
  void clearStatic();

  void drawShape();
  void closeScreen() const;
  std::vector<Object*> exposeShapes(std::string profile) const;
};
