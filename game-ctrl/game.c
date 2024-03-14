#include "stddef.h"
#include "stdint.h"

#include "game.h"
#include "PontCoopScheduler.h"
#include "shapes.h"
#include "canvas.h"


typedef enum { e_idle, e_start, e_newStone, e_down, e_gameOver, e_delay } state_t;

void gameExec(void *handle) {
  static state_t state = e_start;
  static uint8_t delay;

  switch (state) {
    case e_idle:
      break;

    case e_start:
      canvasClear();
      state = e_newStone;
      break;

    case e_newStone:
      stoneCreate();
      if (stoneDraw()) {
        state = e_down;
      } else {
        state = e_gameOver;
      }
      break;
      
    case e_down:
      if (! stoneMoveDown()) {
        state = e_newStone;
      }
      break;

    case e_gameOver:
      for (uint8_t c = 0; c < canvas.width; c++) {
        canvasSetPixel(c, 0, 0x0d);
        canvasSetPixel(c, canvas.height-1, 0x0d);
      }
      for (uint8_t r = 0; r < canvas.height; r++) {
        canvasSetPixel(0, r, 0x0d);
        canvasSetPixel(canvas.width-1, r, 0x0d);
      }
      delay = 10;
      state = e_delay;
      break;

    case e_delay:
      delay--;
      if (delay == 0) {
        state = e_start;
      }
      break;
  }

  canvasShow();
}

void gameInit() {
  schAdd(gameExec, NULL, 0, 1000);
}

