#include "display.hpp"
#include "menu.hpp"
#include "object.hpp"

Menu::Menu(
  Display* display,
  bool debug)
{
  this->display = display;
  this->debug = debug;

  display->attachShape(&button);
}

void Menu::update(){

}
