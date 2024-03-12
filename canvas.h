#ifndef _CANVAS_H_
#define _CANVAS_H_

#include <stdint.h>


#define CANVAS_WIDTH 10
#define CANVAS_HEIGHT 11 

typedef struct {
  uint8_t width;
  uint8_t height;
  uint8_t size;
  uint8_t *canvas;
} canvas_t;

void canvasInit();
void canvasClear();
void canvasSetAll(uint8_t color);
canvas_t *canvasGet();
void canvasShow();
void canvasSetPixel(uint8_t column, uint8_t row, uint8_t color);
void canvasWipeRow(uint8_t row);
uint8_t canvasIsRowFilled(uint8_t row);


#endif // _CANVAS_H_
