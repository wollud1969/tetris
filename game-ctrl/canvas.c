#include <string.h>
#include <stdint.h>

#include <msp430g2553.h>

#include "canvas.h"
#include "spi.h"


static uint8_t canvasStorage[CANVAS_WIDTH * CANVAS_HEIGHT];
const canvas_t canvas = { 
  .height = CANVAS_HEIGHT,
  .width = CANVAS_WIDTH,
  .canvas = canvasStorage
};

static uint8_t miniCanvasStorage[MINI_CANVAS_WIDTH * MINI_CANVAS_HEIGHT];
const canvas_t miniCanvas = { 
  .height = MINI_CANVAS_HEIGHT,
  .width = MINI_CANVAS_WIDTH,
  .canvas = miniCanvasStorage
};

void canvasShow() {
  // wait for signal waiting for data
  while (!(P1IN & BIT3));

  spiSendBegin(e_SPI_CANVAS);

  for (uint8_t i = 0; i < (CANVAS_WIDTH*CANVAS_HEIGHT); i++) {
    if ((*((canvas.canvas)+i) & 0x80) != 0) {
      *((canvas.canvas)+i) &= ~0x80;
      spiSendOctet(i);
      spiSendOctet(*((canvas.canvas)+i));
    }
  }
  for (uint8_t i = 0; i < (MINI_CANVAS_WIDTH*MINI_CANVAS_HEIGHT); i++) {
    if ((*((miniCanvas.canvas)+i) & 0x80) != 0) {
      *((miniCanvas.canvas)+i) &= ~0x80;
      spiSendOctet(i + (CANVAS_HEIGHT*CANVAS_WIDTH));
      spiSendOctet(*((miniCanvas.canvas)+i));
    }
  }
  spiSendOctet(0xfe);

  spiSendEnd(e_SPI_CANVAS);
}

void canvasInit() {
  // P1.3 is signal line
  P1DIR &= ~BIT3;

  canvasClear();
  miniCanvasClear();
  canvasShow();
}

void canvasClear() {
  memset(canvas.canvas, 0x80, CANVAS_WIDTH*CANVAS_HEIGHT);
}

void miniCanvasClear() {
  memset(miniCanvas.canvas, 0x80, MINI_CANVAS_WIDTH*MINI_CANVAS_HEIGHT);
}

//void canvasSetAll(uint8_t color) {
//  memset(canvas.canvas, color + 0x80, CANVAS_WIDTH*CANVAS_HEIGHT);
//}

void canvasSetPixel(uint8_t column, uint8_t row, uint8_t color) {
  *((canvas.canvas) + (row * canvas.width + column)) = (color + 0x80);
}

void miniCanvasSetPixel(uint8_t column, uint8_t row, uint8_t color) {
  *((miniCanvas.canvas) + (row * miniCanvas.width + column)) = (color + 0x80);
}

void canvasWipeRow(uint8_t row) {
  memmove(((canvas.canvas)+canvas.width), canvas.canvas, canvas.width*row);
  for (uint8_t i = 10; i < canvas.width*(row+1); i++) {
    *((canvas.canvas)+i) += 0x80;
  }
  memset(canvas.canvas, 0x80, canvas.width);
}

void canvasFillRow(uint8_t row, uint8_t color) {
  for (uint8_t c = 0; c < canvas.width; c++) {
    canvasSetPixel(c, row, color);
  }
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

uint8_t canvasIsPixelFree(uint8_t column, uint8_t row) {
  return (*((canvas.canvas) + (row * canvas.width + column)) == 0) &&
         (column < canvas.width) &&
         (row < canvas.height);
}

