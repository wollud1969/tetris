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
