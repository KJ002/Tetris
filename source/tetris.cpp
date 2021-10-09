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
  current->meta.appendY(10);
}

void Tetris::moveLeft(){
  current->meta.appendX(-10);
}

void Tetris::moveRight(){
  current->meta.appendX(10);
}

void Tetris::rotate(){
  current->rotateRight();
}

void Tetris::start(){
  spawnShape();

  while (!WindowShouldClose()){

    // Game drawing loop

    BeginDrawing();
    ClearBackground(RAYWHITE);
    display.drawShape();
    EndDrawing();

    if (IsKeyPressed(KEY_A) + IsKeyPressed(KEY_D) + IsKeyPressed(KEY_S) < 2){
      if (IsKeyPressed(KEY_W)) rotate();
      if (IsKeyPressed(KEY_A)) moveLeft();
      if (IsKeyPressed(KEY_D)) moveRight();
      if (IsKeyPressed(KEY_S)) moveDown();
    }
  }

  display.closeScreen();
}
