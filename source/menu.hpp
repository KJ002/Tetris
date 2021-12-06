#include "display.hpp"

class Menu{
private:
  Display* display;
  bool debug;

  bool startGame = false;

public:
  bool shouldStartGame();

  Menu(
    Display* display = nullptr,
    bool debug = false
  );

  void update();
};
