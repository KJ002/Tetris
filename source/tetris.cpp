#include "tetris.hpp"
#include "models.hpp"
#include "object.hpp"
#include <raylib.h>
#include <chrono>

#define timeNow std::chrono::steady_clock::now

// Lazy debugging
#include <iostream>
#define LOG(x) std::cout << x << std::endl;

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

void Tetris::deltaMoveDown(){
  current->meta.appendY(10*deltaTime);
}

void Tetris::rotate(){
  current->rotateRight();
}

void Tetris::start(){
  spawnShape();

  while (!WindowShouldClose()){

    if (lastTime.isSet){
      deltaTime = (timeNow() - lastTime.time).count()/(pow(10, 5));
    }

    if (!lastTime.isSet){
      lastTime.isSet = true;
      deltaTime = 0;
    }

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

    deltaMoveDown();

    lastTime.time = timeNow();
  }

  display.closeScreen();
}
