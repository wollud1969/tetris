#include <stdlib.h>
#include "canvas.h"
#include "PontCoopScheduler.h"


static canvas_t *canvas;

#define MAX_COLOR 0x0d

void displayTestExec(void *args) {
  static uint8_t last = 0xff;
  static uint8_t current = 0;
  static uint8_t color = 0x01;
  static uint8_t state = 1;

  switch (state) {
    case 0:
      for (uint16_t i = 0; i < canvas->height; i++) {
        canvasSetPixel(last, i, 0);
      }
      last = 0xff;
      state = 1;
    case 1:
      if (last != 0xff) {
        *((canvas->canvas)+last) = 0x80;
      }

      last = current;
      *((canvas->canvas)+current) = (color + 0x80);
      current++;
      if (current >= canvas->size) {
        current = 0;
        state = 2;
      }
      break;
    case 2:
      *((canvas->canvas)+last) = 0x80;
      last = 0xff;
      state = 3;
    case 3:
      if (last != 0xff) {
        for (uint16_t i = 0; i < canvas->width; i++) {
          canvasSetPixel(i, last, 0);
        }
      }

      last = current;
      for (uint16_t i = 0; i < canvas->width; i++) {
        canvasSetPixel(i, current, color);
      }
      current++;
      if (current >= canvas->height) {
        current = 0;
        state = 4;
      }
      break;
    case 4:
      for (uint16_t i = 0; i < canvas->width; i++) {
        canvasSetPixel(i, last, 0);
      }
      last = 0xff;
      state = 5;
    case 5:
      if (last != 0xff) {
        for (uint16_t i = 0; i < canvas->height; i++) {
          canvasSetPixel(last, i, 0);
        }
      }

      last = current;
      for (uint16_t i = 0; i < canvas->height; i++) {
        canvasSetPixel(current, i, color);
      }
      current++;
      if (current >= canvas->width) {
        current = 0;
        state = 0;
      }
      break;
  }

  color++;
  if (color > MAX_COLOR) {
    color = 1;
  }

  canvasShow();
}

void displayTestInit() {
  canvas = canvasGet();
  schAdd(displayTestExec, NULL, 0, 50);
}

