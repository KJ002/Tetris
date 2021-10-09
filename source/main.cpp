#include "tetris.hpp"

#define screenWidth 100
#define screenHeight 200
#define screenTitle "Tetris - KJ002"
#define screenFPS 60


int main(){
  Tetris game(screenWidth, screenHeight, screenTitle, screenFPS);

  game.start();

  return 0;
}
