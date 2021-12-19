#include "display.hpp"
#include "menu.hpp"
#include "object.hpp"
#include <raylib.h>

Menu::Menu(
  Display* display,
  bool debug)
{
  this->display = display;
  this->debug = debug;

  display->attachShape(&button.box);
  display->attachShape(&button.contents);

  button.update();
}

void Menu::update(){
  if (button.isClicked())
    display->switchProfile("tetris");
}
