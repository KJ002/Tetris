#include <raylib.h>
#include <iostream>

#include "display.hpp"
#include "object.hpp"

#define LOG(x) std::cout << x << std::endl
#define screenWidth 800
#define screenHeight 450
#define screenTitle "Tetris - KJ002"
#define screenFPS 60


int main(){
  Display screen(
    screenWidth,
    screenHeight,
    screenTitle,
    screenFPS
  );

  TetrisBlock x(100, 10, 0);
  TetrisBlock y(100, 70, 0);

  screen.attachShape(&x);
  screen.attachShape(&y);

  y.active = false;

  while (!WindowShouldClose()){
    BeginDrawing();
    ClearBackground(RAYWHITE);
    screen.drawShape();
    EndDrawing();
    x.colliding(&y);
  }

  screen.closeScreen();

  return 0;
}
