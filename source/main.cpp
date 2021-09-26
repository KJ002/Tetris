#include <raylib.h>
#include <iostream>
#include "models.hpp"
#include <cmath>
#include <vector>

#define LOG(x) std::cout << x << std::endl
#define screenWidth 800
#define screenHeight 450
#define screenTitle "[Example] Ray Marching"
#define screenFPS 60
#define minRadius .0008
#define depth 20


int main(){
  Display screen(
    screenWidth,
    screenHeight,
    screenTitle,
    screenFPS
  );

  BeginDrawing();
  ClearBackground(RAYWHITE);
  EndDrawing();

  screen.closeScreen();

  return 0;
}
