#include "tetris.hpp"
#include "models.hpp"
#include <raylib.h>

Tetris::Tetris(
  int screenWidth,
  int screenHeight,
  char * title,
  int screenFPS
):

  display(screenWidth, screenHeight, title, screenFPS)
{}

void Tetris::spawnShape(){
  TetrisBlock * x = new TetrisBlock((GetScreenWidth()/2)-20, 10, 1);
  shapes.push_back(x);
  display.attachShape(x);
}

void Tetris::start(){
  while (!WindowShouldClose()){

    // Game drawing loop

    BeginDrawing();
    ClearBackground(RAYWHITE);
    display.drawShape();
    EndDrawing();
  }

  display.closeScreen();
}
