#include "shapes.h"
#include "shape_i.h"
#include "canvas.h"
#include "../rgb-driver/colors.h"


#define COLOR _cyan

typedef struct {
  uint8_t x;
  uint8_t y;
} pixel_t;

typedef struct {
  int8_t x;
  int8_t y;
} offset_t;

typedef struct {
  offset_t set[4];
  offset_t reset[4];
  offset_t offset;
} motion_t;

typedef struct {
  uint8_t color;
  pixel_t draw[4];
  motion_t motion[5][4];
} motionTable_t;

const motionTable_t motions[1] = {
  { // i
    .color = _cyan,
    .draw = { { 0, 0}, { 0, 1}, { 0, 2}, { 0, 3} },
    .motion = {
      { 
        // move down
        { .set = { { 0, 4}, { 0, 4}, { 0, 4}, { 0, 4} }, .reset = { { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0} }, .offset = { 0, 1} }, // 0
        { .set = { { 0, 1}, { 1, 1}, { 2, 1}, { 3, 1} }, .reset = { { 0, 0}, { 1, 0}, { 2, 0}, { 3, 0} }, .offset = { 0, 1} }, // 90
        { .set = { { 0, 4}, { 0, 4}, { 0, 4}, { 0, 4} }, .reset = { { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0} }, .offset = { 0, 1} }, // 180
        { .set = { { 0, 1}, { 1, 1}, { 2, 1}, { 3, 1} }, .reset = { { 0, 0}, { 1, 0}, { 2, 0}, { 3, 0} }, .offset = { 0, 1} }  // 270
      },
      { 
        // move left
        { .set = { {-1, 0}, {-1, 1}, {-1, 2}, {-1, 3} }, .reset = { { 0, 0}, { 0, 1}, { 0, 2}, { 0, 3} }, .offset = {-1, 0} }, // 0
        { .set = { {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0} }, .reset = { { 3, 0}, { 3, 0}, { 3, 0}, { 3, 0} }, .offset = { 0, 1} }, // 90
        { .set = { {-1, 0}, {-1, 1}, {-1, 2}, {-1, 3} }, .reset = { { 0, 0}, { 0, 1}, { 0, 2}, { 0, 3} }, .offset = {-1, 0} }, // 180
        { .set = { {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0} }, .reset = { { 3, 0}, { 3, 0}, { 3, 0}, { 3, 0} }, .offset = { 0, 1} }, // 270
      },
      { 
        // move right
        { .set = { { 1, 0}, { 1, 1}, { 1, 2}, { 1, 3} }, .reset = { { 0, 0}, { 0, 1}, { 0, 2}, { 0, 3} }, .offset = { 1, 0} }, // 0
        { .set = { { 4, 0}, { 4, 0}, { 4, 0}, { 4, 0} }, .reset = { { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0} }, .offset = { 1, 0} }, // 90
        { .set = { { 1, 0}, { 1, 1}, { 1, 2}, { 1, 3} }, .reset = { { 0, 0}, { 0, 1}, { 0, 2}, { 0, 3} }, .offset = { 1, 0} }, // 180
        { .set = { { 4, 0}, { 4, 0}, { 4, 0}, { 4, 0} }, .reset = { { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0} }, .offset = { 1, 0} }, // 270
      },
      { 
        // rotate left
        { .set = { {-1, 1}, { 1, 1}, { 2, 1}, { 2, 1} }, .reset = { { 0, 0}, { 0, 2}, { 0, 3}, { 0, 3} }, .offset = {-1, 1} }, // 0
        { .set = { { 1,-2}, { 1,-1}, { 1, 1}, { 1, 1} }, .reset = { { 0, 0}, { 2, 0}, { 3, 0}, { 3, 0} }, .offset = { 1,-2} }, // 90
        { .set = { {-1, 1}, { 1, 1}, { 2, 1}, { 2, 1} }, .reset = { { 0, 0}, { 0, 2}, { 0, 3}, { 0, 3} }, .offset = {-1, 1} }, // 180
        { .set = { { 1,-2}, { 1,-1}, { 1, 1}, { 1, 1} }, .reset = { { 0, 0}, { 2, 0}, { 3, 0}, { 3, 0} }, .offset = { 1,-2} }, // 270
      },
      { 
        // rotate right
        { .set = { {-2, 1}, {-1, 1}, { 1, 1}, { 1, 1} }, .reset = { { 0, 0}, { 0, 2}, { 0, 3}, { 0, 3} }, .offset = {-2, 1} }, // 0
        { .set = { { 2,-2}, { 2,-1}, { 2, 1}, { 2, 1} }, .reset = { { 0, 0}, { 1, 0}, { 3, 0}, { 3, 0} }, .offset = { 2,-2} }, // 90
        { .set = { {-2, 1}, {-1, 1}, { 1, 1}, { 1, 1} }, .reset = { { 0, 0}, { 0, 2}, { 0, 3}, { 0, 3} }, .offset = {-2, 1} }, // 180
        { .set = { { 2,-2}, { 2,-1}, { 2, 1}, { 2, 1} }, .reset = { { 0, 0}, { 1, 0}, { 3, 0}, { 3, 0} }, .offset = { 2,-2} }, // 270
      },
    }
  }
};

uint8_t draw_i() {
  uint8_t res = 0;
  if (canvasIsPixelFree(stone.x + motions[stone.shape].draw[0].x, stone.y + motions[stone.shape].draw[0].y) &&
      canvasIsPixelFree(stone.x + motions[stone.shape].draw[1].x, stone.y + motions[stone.shape].draw[1].y) &&
      canvasIsPixelFree(stone.x + motions[stone.shape].draw[2].x, stone.y + motions[stone.shape].draw[2].y) &&
      canvasIsPixelFree(stone.x + motions[stone.shape].draw[3].x, stone.y + motions[stone.shape].draw[3].y)) {
    canvasSetPixel(stone.x + motions[stone.shape].draw[0].x, stone.y + motions[stone.shape].draw[0].y, motions[stone.shape].color);
    canvasSetPixel(stone.x + motions[stone.shape].draw[1].x, stone.y + motions[stone.shape].draw[1].y, motions[stone.shape].color);
    canvasSetPixel(stone.x + motions[stone.shape].draw[2].x, stone.y + motions[stone.shape].draw[2].y, motions[stone.shape].color);
    canvasSetPixel(stone.x + motions[stone.shape].draw[3].x, stone.y + motions[stone.shape].draw[3].y, motions[stone.shape].color);
    res = 1;
  }
  return res;
}

uint8_t move(direction_t direction) {
  uint8_t res = 0;
  if (canvasIsPixelFree(stone.x + motions[stone.shape].motion[direction][stone.orientation].set[0].x, stone.y + motions[stone.shape].motion[direction][stone.orientation].set[0].y) &&
      canvasIsPixelFree(stone.x + motions[stone.shape].motion[direction][stone.orientation].set[1].x, stone.y + motions[stone.shape].motion[direction][stone.orientation].set[1].y) &&
      canvasIsPixelFree(stone.x + motions[stone.shape].motion[direction][stone.orientation].set[2].x, stone.y + motions[stone.shape].motion[direction][stone.orientation].set[2].y) &&
      canvasIsPixelFree(stone.x + motions[stone.shape].motion[direction][stone.orientation].set[3].x, stone.y + motions[stone.shape].motion[direction][stone.orientation].set[3].y)) {
    canvasSetPixel(stone.x + motions[stone.shape].motion[direction][stone.orientation].reset[0].x, stone.y + motions[stone.shape].motion[direction][stone.orientation].reset[0].y, _off);
    canvasSetPixel(stone.x + motions[stone.shape].motion[direction][stone.orientation].reset[1].x, stone.y + motions[stone.shape].motion[direction][stone.orientation].reset[1].y, _off);
    canvasSetPixel(stone.x + motions[stone.shape].motion[direction][stone.orientation].reset[2].x, stone.y + motions[stone.shape].motion[direction][stone.orientation].reset[2].y, _off);
    canvasSetPixel(stone.x + motions[stone.shape].motion[direction][stone.orientation].reset[3].x, stone.y + motions[stone.shape].motion[direction][stone.orientation].reset[3].y, _off);
    canvasSetPixel(stone.x + motions[stone.shape].motion[direction][stone.orientation].set[0].x, stone.y + motions[stone.shape].motion[direction][stone.orientation].set[0].y, motions[stone.shape].color);
    canvasSetPixel(stone.x + motions[stone.shape].motion[direction][stone.orientation].set[1].x, stone.y + motions[stone.shape].motion[direction][stone.orientation].set[1].y, motions[stone.shape].color);
    canvasSetPixel(stone.x + motions[stone.shape].motion[direction][stone.orientation].set[2].x, stone.y + motions[stone.shape].motion[direction][stone.orientation].set[2].y, motions[stone.shape].color);
    canvasSetPixel(stone.x + motions[stone.shape].motion[direction][stone.orientation].set[3].x, stone.y + motions[stone.shape].motion[direction][stone.orientation].set[3].y, motions[stone.shape].color);
    stone.x += motions[stone.shape].motion[direction][stone.orientation].offset.x;
    stone.y += motions[stone.shape].motion[direction][stone.orientation].offset.y;
    res = 1;
  }
  return res;
}

uint8_t moveDown_i() {
  return move(e_MoveDown);
}

uint8_t moveLeft_i() {
  return move(e_MoveLeft);
}

uint8_t moveRight_i() {
  return move(e_MoveRight);
}

uint8_t rotateLeft_i() {
  uint8_t res = move(e_RotateLeft);
  if (res) {
    stone.orientation = ((orientation_t[]){ e_270, e_0, e_90, e_180 })[stone.orientation];
  }
  return res;
}

uint8_t rotateRight_i() {
  uint8_t res = move(e_RotateRight);
  if (res) {
    stone.orientation = ((orientation_t[]){ e_90, e_180, e_270, e_0 })[stone.orientation];
  }
  return res;
}
