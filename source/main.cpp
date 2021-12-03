#include "tetris.hpp"
#include "display.hpp"

#define screenWidth 100
#define screenHeight 200
#define screenTitle (char*)"Tetris - KJ002"
#define screenFPS 60


int main(){
  Display display(screenWidth, screenHeight, screenTitle, screenFPS);

  Tetris game(screenWidth, screenHeight, screenTitle, screenFPS, &display);

  game.start();

  return 0;
}
