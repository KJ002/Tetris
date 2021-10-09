#pragma once
#include <array>
#include <chrono>
#include "vec2.hpp"

#define timeNow std::chrono::system_clock::now

struct TetrisMeta{
  std::array<bool, 25> map;
  Vec2 origin;
  Vec2 rotationalOrigin;

  int getX() const;
  int getY() const;

  void setX(const int x);
  void setY(const int y);

  int appendX(const int x);
  int appendY(const int y);

  TetrisMeta(int x, int y, int shape);
  TetrisMeta();
};


class timePoint{
private:
  std::chrono::time_point<std::chrono::system_clock> time;
  bool isSet = false;
public:
  timePoint(){
    time = timeNow();
    isSet = true;
  }

  timePoint(std::chrono::time_point<std::chrono::system_clock> time){
    this->time = time;
    isSet = true;
  }

  std::chrono::time_point<std::chrono::system_clock> getTime() const{
    return time;
  }

  void setTime(std::chrono::time_point<std::chrono::system_clock> time){
    this->time = time;
  }

  void now(){
    time = timeNow();
  }
};
