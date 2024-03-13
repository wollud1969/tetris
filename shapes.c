#include <stdint.h>
#include <stddef.h>

#include "shapes.h"
#include "shape_i.h"
#include "shape_o.h"
#include "shape_t.h"
#include "shape_z.h"
#include "shape_s.h"
#include "shape_l.h"
#include "shape_j.h"


typedef enum { e_I=0, e_O, e_T, e_Z, e_S, e_L, e_J, e_ShapeEnd } shape_t;
typedef enum { e_0, e_90, e_180, e_270 } orientation_t;

typedef struct {
  shape_t shape;
  orientation_t orientation;
  uint8_t x; // column
  uint8_t y; // row
} stone_t;

typedef struct {
  uint8_t (* draw)();
  uint8_t (*moveDown)();
  uint8_t (*moveLeft)();
  uint8_t (*moveRight)();
  uint8_t (*rotateLeft)();
  uint8_t (*rotateRight)();
} stoneOperations_t;

const stoneOperations_t stoneOperations[] = {
  { .draw = draw_i, .moveDown = moveDown_i, .moveLeft = moveLeft_i, .moveRight = moveRight_i, .rotateLeft = rotateLeft_i, .rotateRight = rotateRight_i },
  { .draw = draw_o, .moveDown = moveDown_o, .moveLeft = moveLeft_o, .moveRight = moveRight_o, .rotateLeft = rotateLeft_o, .rotateRight = rotateRight_o },
  { .draw = draw_t, .moveDown = moveDown_t, .moveLeft = moveLeft_t, .moveRight = moveRight_t, .rotateLeft = rotateLeft_t, .rotateRight = rotateRight_t },
  { .draw = draw_z, .moveDown = moveDown_z, .moveLeft = moveLeft_z, .moveRight = moveRight_z, .rotateLeft = rotateLeft_z, .rotateRight = rotateRight_z },
  { .draw = draw_s, .moveDown = moveDown_s, .moveLeft = moveLeft_s, .moveRight = moveRight_s, .rotateLeft = rotateLeft_s, .rotateRight = rotateRight_s },
  { .draw = draw_l, .moveDown = moveDown_l, .moveLeft = moveLeft_l, .moveRight = moveRight_l, .rotateLeft = rotateLeft_l, .rotateRight = rotateRight_l },
  { .draw = draw_j, .moveDown = moveDown_j, .moveLeft = moveLeft_j, .moveRight = moveRight_j, .rotateLeft = rotateLeft_j, .rotateRight = rotateRight_j }
};

stone_t stone;

uint8_t draw() {
  return stoneOperations[stone.shape].draw();
}

uint8_t moveDown() {
  return stoneOperations[stone.shape].moveDown();
}

uint8_t moveLeft() {
  return stoneOperations[stone.shape].moveLeft();
}

uint8_t moveRight() {
  return stoneOperations[stone.shape].moveRight();
}

uint8_t rotateLeft() {
  return stoneOperations[stone.shape].rotateLeft();
}

uint8_t rotateRight() {
  return stoneOperations[stone.shape].rotateRight();
}

void shapesExec(void *handle) {
  draw();
}

void shapesInit() {
  shapesExec(NULL);
}






