#include "tetris.hpp"

#define LOG(x) std::cout << x << std::endl
#define screenWidth 450
#define screenHeight 800
#define screenTitle "Tetris - KJ002"
#define screenFPS 60


int main(){
  Tetris game(screenWidth, screenHeight, screenTitle, screenFPS);

  game.start();

  return 0;
}
