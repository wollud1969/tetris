#include "shapes.h"
#include "shape_i.h"
#include "canvas.h"
#include "../rgb-driver/colors.h"


#define COLOR _cyan

uint8_t draw_i() {
  uint8_t res = 0;
  if (canvasIsPixelFree(stone.x, stone.y) &&
      canvasIsPixelFree(stone.x, stone.y+1) &&
      canvasIsPixelFree(stone.x, stone.y+2) &&
      canvasIsPixelFree(stone.x, stone.y+3)) {
    canvasSetPixel(stone.x, stone.y, COLOR);
    canvasSetPixel(stone.x, stone.y+1, COLOR);
    canvasSetPixel(stone.x, stone.y+2, COLOR);
    canvasSetPixel(stone.x, stone.y+3, COLOR);
    res = 1;
  }
  return res;
}

uint8_t moveDown_i() {
  uint8_t res = 0;
  switch (stone.orientation) {
    case e_0:
    case e_180:
      // check whether the destination pixel to the bottom are free
      if (canvasIsPixelFree(stone.x, stone.y+4)) {
        // clear the pixel we move away from 
        canvasSetPixel(stone.x, stone.y, _off);
        // set the pixel we are moving into
        canvasSetPixel(stone.x, stone.y+4, COLOR);
        // update the coordinates
        stone.y += 1;
        // positive result
        res = 1;
      }
      break;
    case e_90:
    case e_270:
      // check whether the destination pixel to the bottom are free
      if (canvasIsPixelFree(stone.x, stone.y+1) &&
          canvasIsPixelFree(stone.x+1, stone.y+1) &&
          canvasIsPixelFree(stone.x+2, stone.y+1) &&
          canvasIsPixelFree(stone.x+3, stone.y+1)) {
        // clear the pixel we move away from 
        canvasSetPixel(stone.x, stone.y, _off);
        canvasSetPixel(stone.x+1, stone.y, _off);
        canvasSetPixel(stone.x+2, stone.y, _off);
        canvasSetPixel(stone.x+3, stone.y, _off);
        // set the pixel we are moving into
        canvasSetPixel(stone.x, stone.y+1, COLOR);
        canvasSetPixel(stone.x+1, stone.y+1, COLOR);
        canvasSetPixel(stone.x+2, stone.y+1, COLOR);
        canvasSetPixel(stone.x+3, stone.y+1, COLOR);
        // update the coordinates
        stone.y += 1;
        // positive result
        res = 1;
      }
      break;
  }
  return res;
}

uint8_t moveLeft_i() {
  uint8_t res = 0;
  switch (stone.orientation) {
    case e_0:
    case e_180:
      // check whether the destination pixel to the bottom are free
      if ((stone.x > 0) &&
          canvasIsPixelFree(stone.x-1, stone.y) &&
          canvasIsPixelFree(stone.x-1, stone.y+1) &&
          canvasIsPixelFree(stone.x-1, stone.y+2) &&
          canvasIsPixelFree(stone.x-1, stone.y+3)) {
        // clear the pixel we move away from 
        canvasSetPixel(stone.x, stone.y, _off);
        canvasSetPixel(stone.x, stone.y+1, _off);
        canvasSetPixel(stone.x, stone.y+2, _off);
        canvasSetPixel(stone.x, stone.y+3, _off);
        // set the pixel we are moving into
        canvasSetPixel(stone.x-1, stone.y, COLOR);
        canvasSetPixel(stone.x-1, stone.y+1, COLOR);
        canvasSetPixel(stone.x-1, stone.y+2, COLOR);
        canvasSetPixel(stone.x-1, stone.y+3, COLOR);
        // update the coordinates
        stone.x -= 1;
        // positive result
        res = 1;
      }
      break;
    case e_90:
    case e_270:
      // check whether the destination pixel to the bottom are free
      if ((stone.x > 0) &&
          canvasIsPixelFree(stone.x-1, stone.y)) {
        // clear the pixel we move away from 
        canvasSetPixel(stone.x+3, stone.y, _off);
        // set the pixel we are moving into
        canvasSetPixel(stone.x-1, stone.y, COLOR);
        // update the coordinates
        stone.x -= 1;
        // positive result
        res = 1;
      }
      break;
  }
  return res;
}

uint8_t moveRight_i() {
  uint8_t res = 0;
  switch (stone.orientation) {
    case e_0:
    case e_180:
      // check whether the destination pixel to the bottom are free
      if (canvasIsPixelFree(stone.x+1, stone.y) &&
          canvasIsPixelFree(stone.x+1, stone.y+1) &&
          canvasIsPixelFree(stone.x+1, stone.y+2) &&
          canvasIsPixelFree(stone.x+1, stone.y+3)) {
        // clear the pixel we move away from 
        canvasSetPixel(stone.x, stone.y, _off);
        canvasSetPixel(stone.x, stone.y+1, _off);
        canvasSetPixel(stone.x, stone.y+2, _off);
        canvasSetPixel(stone.x, stone.y+3, _off);
        // set the pixel we are moving into
        canvasSetPixel(stone.x+1, stone.y, COLOR);
        canvasSetPixel(stone.x+1, stone.y+1, COLOR);
        canvasSetPixel(stone.x+1, stone.y+2, COLOR);
        canvasSetPixel(stone.x+1, stone.y+3, COLOR);
        // update the coordinates
        stone.x += 1;
        // positive result
        res = 1;
      }
      break;
    case e_90:
    case e_270:
      // check whether the destination pixel to the bottom are free
      if (canvasIsPixelFree(stone.x+4, stone.y)) {
        // clear the pixel we move away from 
        canvasSetPixel(stone.x, stone.y, _off);
        // set the pixel we are moving into
        canvasSetPixel(stone.x+4, stone.y, COLOR);
        // update the coordinates
        stone.x += 1;
        // positive result
        res = 1;
      }
      break;
  }
  return res;
}

uint8_t rotateLeft_i() {
  uint8_t res = 0;
  switch (stone.orientation) {
    case e_0:
    case e_180:
      // check whether the destination pixel to the bottom are free
      if (stone.x > 0 &&
          canvasIsPixelFree(stone.x-1, stone.y+1) &&
          canvasIsPixelFree(stone.x+1, stone.y+1) &&
          canvasIsPixelFree(stone.x+2, stone.y+1)) {
        // clear the pixel we move away from 
        canvasSetPixel(stone.x, stone.y, _off);
        canvasSetPixel(stone.x, stone.y+1, _off);
        canvasSetPixel(stone.x, stone.y+2, _off);
        canvasSetPixel(stone.x, stone.y+3, _off);
        // set the pixel we are moving into
        canvasSetPixel(stone.x-1, stone.y+1, COLOR);
        canvasSetPixel(stone.x,   stone.y+1, COLOR);
        canvasSetPixel(stone.x+1, stone.y+1, COLOR);
        canvasSetPixel(stone.x+2, stone.y+1, COLOR);
        // update the coordinates
        stone.x -= 1;
        stone.y += 1;
        if (stone.orientation == e_0) {
          stone.orientation = e_270;
        } else {
          stone.orientation = e_90;
        }
        // positive result
        res = 1;
      }
      break;
    case e_90:
    case e_270:
      // check whether the destination pixel to the bottom are free
      if (stone.y > 1 &&
          canvasIsPixelFree(stone.x+1, stone.y-2) &&
          canvasIsPixelFree(stone.x+1, stone.y-1) &&
          canvasIsPixelFree(stone.x+1, stone.y+1)) {
        // clear the pixel we move away from 
        canvasSetPixel(stone.x, stone.y, _off);
        canvasSetPixel(stone.x+2, stone.y, _off);
        canvasSetPixel(stone.x+3, stone.y, _off);
        // set the pixel we are moving into
        canvasSetPixel(stone.x+1, stone.y-2, COLOR);
        canvasSetPixel(stone.x+1, stone.y-1, COLOR);
        canvasSetPixel(stone.x+1, stone.y+1, COLOR);
        // update the coordinates
        stone.x += 1;
        stone.y -= 2;
        if (stone.orientation == e_90) {
          stone.orientation = e_0;
        } else {
          stone.orientation = e_180;
        }
        // positive result
        res = 1;
      }
      break;
  }
  return res;
}

uint8_t rotateRight_i() {
  uint8_t res = 0;
  switch (stone.orientation) {
    case e_0:
    case e_180:
      // check whether the destination pixel to the bottom are free
      if (stone.x > 1 &&
          canvasIsPixelFree(stone.x-2, stone.y+1) &&
          canvasIsPixelFree(stone.x-1, stone.y+1) &&
          canvasIsPixelFree(stone.x+1, stone.y+1)) {
        // clear the pixel we move away from 
        canvasSetPixel(stone.x, stone.y, _off);
        canvasSetPixel(stone.x, stone.y+2, _off);
        canvasSetPixel(stone.x, stone.y+3, _off);
        // set the pixel we are moving into
        canvasSetPixel(stone.x-2, stone.y+1, COLOR);
        canvasSetPixel(stone.x-1, stone.y+1, COLOR);
        canvasSetPixel(stone.x+1, stone.y+1, COLOR);
        // update the coordinates
        stone.x -= 2;
        stone.y += 1;
        if (stone.orientation == e_0) {
          stone.orientation = e_270;
        } else {
          stone.orientation = e_90;
        }
        // positive result
        res = 1;
      }
      break;
    case e_90:
    case e_270:
      // check whether the destination pixel to the bottom are free
      if (stone.y > 1 &&
          canvasIsPixelFree(stone.x+2, stone.y-2) &&
          canvasIsPixelFree(stone.x+2, stone.y-1) &&
          canvasIsPixelFree(stone.x+2, stone.y+1)) {
        // clear the pixel we move away from 
        canvasSetPixel(stone.x, stone.y, _off);
        canvasSetPixel(stone.x+1, stone.y, _off);
        canvasSetPixel(stone.x+3, stone.y, _off);
        // set the pixel we are moving into
        canvasSetPixel(stone.x+2, stone.y-2, COLOR);
        canvasSetPixel(stone.x+2, stone.y-1, COLOR);
        canvasSetPixel(stone.x+2, stone.y+1, COLOR);
        // update the coordinates
        stone.x += 2;
        stone.y -= 2;
        if (stone.orientation == e_90) {
          stone.orientation = e_0;
        } else {
          stone.orientation = e_180;
        }
        // positive result
        res = 1;
      }
      break;
  }
  return res;
}
