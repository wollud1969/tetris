#include <stdlib.h>
#include <string.h>
#include "canvas.h"
#include "PontCoopScheduler.h"
#include "displayTest2.h"




typedef enum { e_idle, e_start, e_fillArea, e_placeObject, e_wipeLines_7, e_wipeLines_8, e_wipeLines_9, e_wipeLines_10 } t_state;

void displayTest2Exec(void *args) {
  static t_state state = e_start;

  switch (state) {
    case e_idle:
      break;

    case e_start:
      state = e_fillArea;
      break;

    case e_fillArea:
      memset((canvas.canvas)+(canvas.width*7), 0x81, canvas.width);
      memset((canvas.canvas)+(canvas.width*8), 0x8d, canvas.width);
      memset((canvas.canvas)+(canvas.width*9), 0x82, canvas.width);
      memset((canvas.canvas)+(canvas.width*10), 0x88, canvas.width);
      for (uint8_t i = 0; i < canvas.width; i++) {
        if (i != 4 && i != 5) {
          canvasSetPixel(i, 6, 0x05);
        }
      }
      state = e_placeObject;
      break;

    case e_placeObject:
      canvasSetPixel(4, 0, 0x04);
      canvasSetPixel(5, 0, 0x04);
      canvasSetPixel(6, 0, 0x04);
      canvasSetPixel(5, 1, 0x04);
      state = e_wipeLines_7;
      break;

    case e_wipeLines_7:
      canvasWipeRow(7);
      state = e_wipeLines_8;
      break;

    case e_wipeLines_8:
      canvasWipeRow(8);
      state = e_wipeLines_9;
      break;

    case e_wipeLines_9:
      canvasWipeRow(9);
      state = e_wipeLines_10;
      break;

    case e_wipeLines_10:
      canvasWipeRow(10);
      state = e_idle;
      break;

    default:
      state = e_idle;
      break;
  }

  canvasShow();
}

void displayTest2Init() {
  schAdd(displayTest2Exec, NULL, 0, 5000);
}

