#include <raylib.h>
#include "object.hpp"

Square::Square(int x, int y, int width, int height){
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

void Square::draw() const{
    DrawRectangle(x, y, width, height, BLUE);
}
