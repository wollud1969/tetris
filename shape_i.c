#include "shapes.h"
#include "shape_i.h"
#include "canvas.h"

uint8_t draw_i() {
  canvasSetPixel(stone.x, stone.y, 0x01);
  canvasSetPixel(stone.x, stone.y+1, 0x01);
  canvasSetPixel(stone.x, stone.y+2, 0x01);
  canvasSetPixel(stone.x, stone.y+3, 0x01);
  return 1;
}

uint8_t moveDown_i() {
  return 1;
}

uint8_t moveLeft_i() {
  return 1;
}

uint8_t moveRight_i() {
  return 1;
}

uint8_t rotateLeft_i() {
  return 1;
}

uint8_t rotateRight_i() {
  return 1;
}
