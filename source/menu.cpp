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

  button.setX(GetScreenWidth()/2-button.getWidth()/2);
  button.setY(GetScreenHeight()/2-button.getHeight()/2);

  display->attachShape(&button.box);
  display->attachShape(&button.contents);
}

void Menu::update(){
  if (button.isClicked())
    display->switchProfile("tetris");
}
