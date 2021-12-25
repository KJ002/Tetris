#include "display.hpp"
#include "menu.hpp"
#include "tetris.hpp"
#include "object.hpp"
#include <raylib.h>
#include <string>

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
  display->attachShape(scoreObj);
}

void Menu::update(){
  // Switch display profile to tetris

  if (button.isClicked()){
    display->switchProfile("tetris");
    return;
  }

  // Update faded tetris blocks

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

  // Update score

  score = game->getScore();
  scoreObj->text = std::to_string(score);
  scoreObj->x = GetScreenWidth()/2-MeasureText(std::to_string(score).data(), scoreObj->fontSize)/2;
}
