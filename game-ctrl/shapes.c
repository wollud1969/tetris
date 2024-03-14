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

void shapesInit() {
  stone.shape = e_ShapeInvalid;
}

void stoneCreate() {
  stone.shape = e_I;
  stone.orientation = e_0;
  stone.x = 5;
  stone.y = 0;
}

// all of them return 1 in case of success and 0 in case of error
uint8_t stoneDraw() {
  return stoneOperations[stone.shape].draw();
}

uint8_t stoneMoveDown() {
  return stoneOperations[stone.shape].moveDown();
}

uint8_t stoneMoveLeft() {
  return stoneOperations[stone.shape].moveLeft();
}

uint8_t stoneMoveRight() {
  return stoneOperations[stone.shape].moveRight();
}

uint8_t stoneRotateLeft() {
  return stoneOperations[stone.shape].rotateLeft();
}

uint8_t stoneRotateRight() {
  return stoneOperations[stone.shape].rotateRight();
}







