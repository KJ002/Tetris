#include "display.hpp"
#include "menu.hpp"

Menu::Menu(
  Display* display,
  bool debug)
{
  this->display = display;
  this->debug = debug;
}
