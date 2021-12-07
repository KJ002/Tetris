#include "tetris.hpp"
#include "menu.hpp"
#include "display.hpp"
#include <raylib.h>

#define screenWidth 100
#define screenHeight 200
#define screenTitle (char*)"Tetris - KJ002"
#define screenFPS 60


int main(){
  Display display(screenWidth, screenHeight, screenTitle, screenFPS);

  display.switchProfile("tetris");
  Tetris game(&display);

  display.switchProfile("menu");
  Menu menu(&display);

  while (!WindowShouldClose()){
    BeginDrawing();
    ClearBackground(BLACK);
    display.drawShape();
    EndDrawing();
    menu.update();
    game.update();
  }

  display.closeScreen();

  return 0;
}
