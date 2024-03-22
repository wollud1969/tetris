#ifndef _CANVAS_H_
#define _CANVAS_H_

#include <stdint.h>

// Definition of CANVAS_WIDTH and CANVAS_HEIGHT
// imported from rgb-driver
#include "../rgb-driver/canvasSize.h"


typedef struct {
  const uint8_t width;
  const uint8_t height;
  const uint8_t size;
  uint8_t * const canvas;
} canvas_t;

void canvasInit();
void canvasClear();
void miniCanvasClear();
//void canvasSetAll(uint8_t color);
void canvasShow();
void canvasSetPixel(uint8_t column, uint8_t row, uint8_t color);
void miniCanvasSetPixel(uint8_t column, uint8_t row, uint8_t color);
uint8_t canvasIsPixelFree(uint8_t column, uint8_t row);
void canvasWipeRow(uint8_t row);
void canvasFillRow(uint8_t row, uint8_t color);
uint8_t canvasIsRowFilled(uint8_t row);

#endif // _CANVAS_H_
