#include "tetris.hpp"
#include "display.hpp"
#include <raylib.h>

#define screenWidth 100
#define screenHeight 200
#define screenTitle (char*)"Tetris - KJ002"
#define screenFPS 60


int main(){
  Display display(screenWidth, screenHeight, screenTitle, screenFPS);

  Tetris game(screenWidth, screenHeight, screenTitle, screenFPS, &display);

  while (!WindowShouldClose())
    game.update();

  display.closeScreen();

  return 0;
}
