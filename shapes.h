#ifndef _SHAPES_H_
#define _SHAPES_H_

#include <stdint.h>

void stoneCreate();
uint8_t stoneDraw();
uint8_t stoneMoveDown();
uint8_t stoneMoveLeft();
uint8_t stoneMoveRight();
uint8_t stoneRotateLeft();
uint8_t stoneRotateRight();


typedef enum { e_I=0, e_O, e_T, e_Z, e_S, e_L, e_J, e_ShapeEnd } shape_t;
typedef enum { e_0, e_90, e_180, e_270 } orientation_t;

typedef struct {
  shape_t shape;
  orientation_t orientation;
  uint8_t x; // column
  uint8_t y; // row
} stone_t;


extern stone_t stone;

#endif // _SHAPES_H_
