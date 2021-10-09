#include "tetris.hpp"
#include "models.hpp"
#include "object.hpp"
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

  current = x;
  shapes.push_back(x);
  display.attachShape(x);
}

void Tetris::moveDown(){
  current->meta.appendY(20);
}

void Tetris::start(){
  spawnShape();

  while (!WindowShouldClose()){

    // Game drawing loop

    BeginDrawing();
    ClearBackground(RAYWHITE);
    display.drawShape();
    EndDrawing();

    if (IsKeyDown(KEY_S)) moveDown();
  }

  display.closeScreen();
}