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
}

void Menu::update(){
  if (button.isClicked())
    display->switchProfile("tetris");


  for (size_t tetrisIndex = 0; tetrisIndex < display->exposeShapes("tetris").size(); tetrisIndex++){
    for (size_t menuIndex = 0; menuIndex < display->exposeShapes("menu").size(); menuIndex++){
      if (display->exposeShapes("tetris")[tetrisIndex] == display->exposeShapes("menu")[menuIndex])
        break;
      if (menuIndex == display->exposeShapes("menu").size()-1)
        display->attachShape(display->exposeShapes("tetris")[tetrisIndex]);
    }
  }
}
