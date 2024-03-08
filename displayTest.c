#include <stdlib.h>
#include "canvas.h"
#include "PontCoopScheduler.h"


static canvas_t *canvas;
static uint8_t lastPixel = 0xff;
static uint8_t currentPixel = 0;

void displayTestExec(void *args) {
  if (lastPixel != 0xff) {
    *((canvas->canvas)+lastPixel) = 0x80;
  }

  lastPixel = currentPixel;
  *((canvas->canvas)+currentPixel) = 0x81;
  currentPixel++;
  if (currentPixel >= canvas->size) {
    currentPixel = 0;
  }

  canvasShow();
}

void displayTestInit() {
  canvas = canvasGet();
  schAdd(displayTestExec, NULL, 0, 50);
}

