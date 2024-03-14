#include <stdlib.h>
#include <string.h>
#include "canvas.h"
#include "PontCoopScheduler.h"
#include "displayTest3.h"
#include "led.h"


typedef enum { e_idle, e_delay, e_start, e_fillArea, e_placeObject, e_preWipeLines, e_wipeLines } t_state;

void displayTest3Exec(void *args) {
  static t_state state = e_start;
  static uint8_t wipeLineHelper = 0;

  ledBlueToggle();

  switch (state) {
    case e_idle:
      state = e_delay;
      break;

    case e_delay:
      state = e_start;
      break;

    case e_start:
      canvasClear();
      state = e_fillArea;
      break;

    case e_fillArea:
      memset((canvas.canvas)+(canvas.width*7), 0x82, canvas.width);
      memset((canvas.canvas)+(canvas.width*8), 0x83, canvas.width);
      memset((canvas.canvas)+(canvas.width*9), 0x84, canvas.width);
      memset((canvas.canvas)+(canvas.width*10), 0x85, canvas.width);
      for (uint8_t i = 0; i < canvas.width; i++) {
        if (i != 4 && i != 5) {
          canvasSetPixel(i, 6, 0x01);
        }
      }
      state = e_placeObject;
      break;

    case e_placeObject:
      canvasSetPixel(4, 0, 0x04);
      canvasSetPixel(5, 0, 0x04);
      canvasSetPixel(6, 0, 0x04);
      canvasSetPixel(5, 1, 0x04);
      state = e_preWipeLines;
      break;

    case e_preWipeLines:
      wipeLineHelper = 0;
      state = e_wipeLines;
      // no break
      
    case e_wipeLines:
      if (canvasIsRowFilled(wipeLineHelper) == 1) {
        canvasWipeRow(wipeLineHelper);
      }
      wipeLineHelper++;
      if (wipeLineHelper >= canvas.height) {
        state = e_idle;
      }
      break;

    default:
      state = e_idle;
      break;
  }

  canvasShow();
}

void displayTest3Init() {
  schAdd(displayTest3Exec, NULL, 0, 1000);
}

