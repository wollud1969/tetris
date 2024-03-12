#include <string.h>
#include <stdint.h>

#include "canvas.h"
#include "displayDriver.h"


static uint8_t canvasStorage[CANVAS_WIDTH * CANVAS_HEIGHT];
const canvas_t canvas = { 
  .height = CANVAS_HEIGHT,
  .width = CANVAS_WIDTH,
  .size = CANVAS_WIDTH * CANVAS_HEIGHT,
  .canvas = canvasStorage
};

void canvasInit() {
  canvasClear();
  displayDriverTransferCanvas();
}

void canvasClear() {
  memset(canvas.canvas, 0x80, canvas.size);
}

void canvasSetAll(uint8_t color) {
  memset(canvas.canvas, color + 0x80, canvas.size);
}

void canvasShow() {
  displayDriverTransferCanvas();
}

void canvasSetPixel(uint8_t column, uint8_t row, uint8_t color) {
  *((canvas.canvas) + (row * canvas.width + column)) = (color + 0x80);
}

void canvasWipeRow(uint8_t row) {
  memmove(((canvas.canvas)+canvas.width), canvas.canvas, canvas.width*row);
  for (uint8_t i = 10; i < canvas.width*(row+1); i++) {
    *((canvas.canvas)+i) += 0x80;
  }
  memset(canvas.canvas, 0x80, canvas.width);
}

uint8_t canvasIsRowFilled(uint8_t row) {
  uint8_t res = 1;
  for (uint8_t column = 0; column < canvas.width; column++) {
    if (*((canvas.canvas) + (row * canvas.width + column)) == 0) {
      res = 0;
      break;
    }
  }
  return res;
}

