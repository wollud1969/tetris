#include <stdlib.h>
#include "canvas.h"
#include "PontCoopScheduler.h"


#define MAX_COLOR 0x0d

typedef enum {
  e_WIPE_LAST_COLUMN_DOWN,
  e_PIXELS_UP,
  e_WIPE_LAST_PIXEL_UP,
  e_PIXELS_DOWN,
  e_WIPE_LAST_PIXEL_DOWN,
  e_ROWS_UP,
  e_WIPE_LAST_ROW_UP,
  e_ROWS_DOWN,
  e_WIPE_LAST_ROW_DOWN,
  e_COLUMNS_UP,
  e_WIPE_LAST_COLUMN_UP,
  e_COLUMNS_DOWN
} t_State;

void displayTestExec(void *args) {
  static int16_t last = 0xff;
  static int16_t current = 0;
  static uint8_t color = 0x01;
  static t_State state = e_PIXELS_UP;

  switch (state) {
    // wipe last column
    case e_WIPE_LAST_COLUMN_DOWN:
      for (uint16_t i = 0; i < canvas.height; i++) {
        canvasSetPixel(last, i, 0);
      }
      last = 0xff;
      state = e_PIXELS_UP;
    // pixels up
    case e_PIXELS_UP:
      if (last != 0xff) {
        *((canvas.canvas)+last) = 0x80;
      }

      last = current;
      *((canvas.canvas)+current) = (color + 0x80);
      current++;
      if (current >= canvas.size) {
        current = 0;
        state = e_WIPE_LAST_PIXEL_UP;
      }
      break;
    // wipe last pixel
    case e_WIPE_LAST_PIXEL_UP:
      *((canvas.canvas)+last) = 0x80;
      last = 0xff;
      current = canvas.size - 1;
      state = e_PIXELS_DOWN;
    // pixels down
    case e_PIXELS_DOWN:
      if (last != 0xff) {
        *((canvas.canvas)+last) = 0x80;
      }

      last = current;
      *((canvas.canvas)+current) = (color + 0x80);
      current--;
      if (current < 0) {
        current = 0;
        state = e_WIPE_LAST_PIXEL_DOWN;
      }
      break;
    // wipe last pixel
    case e_WIPE_LAST_PIXEL_DOWN:
      *((canvas.canvas)+last) = 0x80;
      last = 0xff;
      state = e_ROWS_UP;
    // rows up
    case e_ROWS_UP:
      if (last != 0xff) {
        for (uint16_t i = 0; i < canvas.width; i++) {
          canvasSetPixel(i, last, 0);
        }
      }

      last = current;
      for (uint16_t i = 0; i < canvas.width; i++) {
        canvasSetPixel(i, current, color);
      }
      current++;
      if (current >= canvas.height) {
        current = 0;
        state = e_WIPE_LAST_ROW_UP;
      }
      break;
    // wipe last row
    case e_WIPE_LAST_ROW_UP:
      for (uint16_t i = 0; i < canvas.width; i++) {
        canvasSetPixel(i, last, 0);
      }
      last = 0xff;
      current = canvas.height - 1;
      state = e_ROWS_DOWN;
    // rows down
    case e_ROWS_DOWN:
      if (last != 0xff) {
        for (uint16_t i = 0; i < canvas.width; i++) {
          canvasSetPixel(i, last, 0);
        }
      }

      last = current;
      for (uint16_t i = 0; i < canvas.width; i++) {
        canvasSetPixel(i, current, color);
      }
      current--;
      if (current < 0) {
        current = 0;
        state = e_WIPE_LAST_ROW_DOWN;
      }
      break;
    // wipe last row
    case e_WIPE_LAST_ROW_DOWN:
      for (uint16_t i = 0; i < canvas.width; i++) {
        canvasSetPixel(i, last, 0);
      }
      last = 0xff;
      state = e_COLUMNS_UP;
    // columns up
    case e_COLUMNS_UP:
      if (last != 0xff) {
        for (uint16_t i = 0; i < canvas.height; i++) {
          canvasSetPixel(last, i, 0);
        }
      }

      last = current;
      for (uint16_t i = 0; i < canvas.height; i++) {
        canvasSetPixel(current, i, color);
      }
      current++;
      if (current >= canvas.width) {
        current = 0;
        state = e_WIPE_LAST_COLUMN_UP;
      }
      break;
    // wipe last column
    case e_WIPE_LAST_COLUMN_UP:
      for (uint16_t i = 0; i < canvas.height; i++) {
        canvasSetPixel(last, i, 0);
      }
      last = 0xff;
      current = canvas.width - 1;
      state = e_COLUMNS_DOWN;
    // columns down
    case e_COLUMNS_DOWN:
      if (last != 0xff) {
        for (uint16_t i = 0; i < canvas.height; i++) {
          canvasSetPixel(last, i, 0);
        }
      }

      last = current;
      for (uint16_t i = 0; i < canvas.height; i++) {
        canvasSetPixel(current, i, color);
      }
      current--;
      if (current < 0) {
        current = 0;
        state = e_WIPE_LAST_COLUMN_DOWN;
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
  schAdd(displayTestExec, NULL, 0, 50);
}

