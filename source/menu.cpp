#include "display.hpp"
#include "menu.hpp"
#include "tetris.hpp"
#include "object.hpp"
#include <raylib.h>

Menu::Menu(
  Display* display,
  Tetris* game,
  bool debug)
{
  this->display = display;
  this->game = game;
  this->debug = debug;

  display->attachShape(&button.box);
  display->attachShape(&button.contents);
}

void Menu::update(){
  if (button.isClicked()){
    display->switchProfile("tetris");
    return;
  }

  for (TetrisBlock* block : tetrisBlocks){
    display->removeShape(block);
    delete block;
  }

  tetrisBlocks.clear();

  for (TetrisBlock* block : *(game->exposeTetrisBlocks())){
    TetrisBlock* copy = new TetrisBlock(*block);
    copy->meta.colour.a = 50;
    tetrisBlocks.push_back(copy);
    display->attachShape(copy);
  }
}
