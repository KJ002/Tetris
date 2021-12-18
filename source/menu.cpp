#include "display.hpp"
#include "menu.hpp"
#include "object.hpp"
#include <iostream>

Menu::Menu(
  Display* display,
  bool debug)
{
  this->display = display;
  this->debug = debug;

  display->attachShape(&button.box);
  display->attachShape(&button.contents);
}

void Menu::update(){
  if (button.isClicked())
    display->switchProfile("tetris");
}
