#include <string.h>
#include <stdint.h>

#include "canvas.h"
#include "displayDriver.h"


static canvas_t canvas;
static uint8_t canvasStorage[CANVAS_WIDTH * CANVAS_HEIGHT];

void canvasInit() {
  canvas.height = CANVAS_HEIGHT;
  canvas.width = CANVAS_WIDTH;
  canvas.size = CANVAS_HEIGHT * CANVAS_WIDTH;
  canvas.canvas = canvasStorage;

  // Bit7 signals need to be transfered for octet
  memset(canvasStorage, 0x80, canvas.size);

  displayDriverTransferCanvas();
}

canvas_t *canvasGet() {
  return &canvas;
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

