#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

#include "shapes.h"
#include "myrand.h"
#include "canvas.h"
#include "../rgb-driver/colors.h"




typedef enum { e_I=0, e_O, e_T, e_Z, e_S, e_L, e_J, e_ShapeInvalid } shape_t;
typedef enum { e_MoveDown, e_MoveLeft, e_MoveRight, e_RotateLeft, e_RotateRight } direction_t;
typedef enum { e_0, e_90, e_180, e_270, e_Keep } orientation_t;

typedef struct {
  shape_t shape;
  orientation_t orientation;
  uint8_t x; // column
  uint8_t y; // row
  bool locked;
} stone_t;

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
  uint8_t nullRotation;
  pixel_t draw[4];
  motion_t motion[5][4];
} motionTable_t;

const motionTable_t motions[7] = { // size = number of implemented stones
  { // I
    .color = _cyan,
    .nullRotation = 0,
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
        { .set = { {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0} }, .reset = { { 3, 0}, { 3, 0}, { 3, 0}, { 3, 0} }, .offset = {-1, 0} }, // 90
        { .set = { {-1, 0}, {-1, 1}, {-1, 2}, {-1, 3} }, .reset = { { 0, 0}, { 0, 1}, { 0, 2}, { 0, 3} }, .offset = {-1, 0} }, // 180
        { .set = { {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0} }, .reset = { { 3, 0}, { 3, 0}, { 3, 0}, { 3, 0} }, .offset = {-1, 0} }, // 270
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
        { .set = { { 1,-1}, { 1, 1}, { 1, 2}, { 1, 2} }, .reset = { { 0, 0}, { 2, 0}, { 3, 0}, { 3, 0} }, .offset = { 1,-1} }, // 90
        { .set = { {-2, 1}, {-1, 1}, { 1, 1}, { 1, 1} }, .reset = { { 0, 0}, { 0, 2}, { 0, 3}, { 0, 3} }, .offset = {-2, 1} }, // 180
        { .set = { { 1,-1}, { 1, 1}, { 1, 2}, { 1, 2} }, .reset = { { 0, 0}, { 2, 0}, { 3, 0}, { 3, 0} }, .offset = { 1,-1} }, // 270
      },
    }
  },
  { // O
    .color = _yellow,
    .nullRotation = 1,
    .draw = { { 0, 0}, { 0, 1}, { 1, 0}, { 1, 1} },
    .motion = {
      {
        // move down
        { .set = { { 0, 2}, { 1, 2}, { 1, 2}, { 1, 2} }, .reset = { { 0, 0}, { 1, 0}, { 1, 0}, { 1, 0} }, .offset = { 0, 1} }, // 0
        { .set = { { 0, 2}, { 1, 2}, { 1, 2}, { 1, 2} }, .reset = { { 0, 0}, { 1, 0}, { 1, 0}, { 1, 0} }, .offset = { 0, 1} }, // 90
        { .set = { { 0, 2}, { 1, 2}, { 1, 2}, { 1, 2} }, .reset = { { 0, 0}, { 1, 0}, { 1, 0}, { 1, 0} }, .offset = { 0, 1} }, // 180
        { .set = { { 0, 2}, { 1, 2}, { 1, 2}, { 1, 2} }, .reset = { { 0, 0}, { 1, 0}, { 1, 0}, { 1, 0} }, .offset = { 0, 1} }, // 270
      },
      {
        // move left
        { .set = { {-1, 0}, {-1, 1}, {-1, 1}, {-1, 1} }, .reset = { { 1, 0}, { 1, 1}, { 1, 1}, { 1, 1} }, .offset = {-1, 0} }, // 0
        { .set = { {-1, 0}, {-1, 1}, {-1, 1}, {-1, 1} }, .reset = { { 1, 0}, { 1, 1}, { 1, 1}, { 1, 1} }, .offset = {-1, 0} }, // 90
        { .set = { {-1, 0}, {-1, 1}, {-1, 1}, {-1, 1} }, .reset = { { 1, 0}, { 1, 1}, { 1, 1}, { 1, 1} }, .offset = {-1, 0} }, // 180
        { .set = { {-1, 0}, {-1, 1}, {-1, 1}, {-1, 1} }, .reset = { { 1, 0}, { 1, 1}, { 1, 1}, { 1, 1} }, .offset = {-1, 0} }, // 270
      },
      {
        // move right
        { .set = { { 2, 0}, { 2, 1}, { 2, 1}, { 2, 1} }, .reset = { { 0, 0}, { 0, 1}, { 0, 1}, { 0, 1} }, .offset = { 1, 0} }, // 0
        { .set = { { 2, 0}, { 2, 1}, { 2, 1}, { 2, 1} }, .reset = { { 0, 0}, { 0, 1}, { 0, 1}, { 0, 1} }, .offset = { 1, 0} }, // 90
        { .set = { { 2, 0}, { 2, 1}, { 2, 1}, { 2, 1} }, .reset = { { 0, 0}, { 0, 1}, { 0, 1}, { 0, 1} }, .offset = { 1, 0} }, // 180
        { .set = { { 2, 0}, { 2, 1}, { 2, 1}, { 2, 1} }, .reset = { { 0, 0}, { 0, 1}, { 0, 1}, { 0, 1} }, .offset = { 1, 0} }, // 270
      },
      {
        // rotate left
        { .set = { { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0} }, .reset = { { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0} }, .offset = { 0, 0} }, // 0
        { .set = { { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0} }, .reset = { { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0} }, .offset = { 0, 0} }, // 90
        { .set = { { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0} }, .reset = { { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0} }, .offset = { 0, 0} }, // 180
        { .set = { { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0} }, .reset = { { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0} }, .offset = { 0, 0} }, // 270
      },
      {
        // rotate right
        { .set = { { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0} }, .reset = { { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0} }, .offset = { 0, 0} }, // 0
        { .set = { { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0} }, .reset = { { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0} }, .offset = { 0, 0} }, // 90
        { .set = { { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0} }, .reset = { { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0} }, .offset = { 0, 0} }, // 180
        { .set = { { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0} }, .reset = { { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0} }, .offset = { 0, 0} }, // 270
      },
    }
  },
  { // T
    .color = _violet,
    .nullRotation = 0,
    .draw = { { 0, 0}, { 1, 0}, { 2, 0}, { 1, 1} },
    .motion = {
      {
        // move down
        { .set = { { 0, 1}, { 2, 1}, { 1, 2}, { 1, 2} }, .reset = { { 0, 0}, { 1, 0}, { 2, 0}, { 2, 0} }, .offset = { 0, 1} }, // 0
        { .set = { { 0, 2}, { 1, 3}, { 1, 3}, { 1, 3} }, .reset = { { 1, 0}, { 0, 1}, { 0, 1}, { 0, 1} }, .offset = { 0, 1} }, // 90
        { .set = { { 0, 2}, { 1, 2}, { 2, 2}, { 2, 2} }, .reset = { { 1, 0}, { 0, 1}, { 2, 1}, { 2, 1} }, .offset = { 0, 1} }, // 180
        { .set = { { 0, 3}, { 1, 2}, { 1, 2}, { 1, 2} }, .reset = { { 0, 0}, { 1, 1}, { 1, 1}, { 1, 1} }, .offset = { 0, 1} }, // 270
      },
      {
        // move left
        { .set = { {-1, 0}, { 0, 1}, { 0, 1}, { 0, 1} }, .reset = { { 1, 1}, { 2, 0}, { 2, 0}, { 2, 0} }, .offset = {-1, 0} }, // 0
        { .set = { { 0, 0}, {-1, 1}, { 0, 2}, { 0, 2} }, .reset = { { 1, 0}, { 1, 1}, { 1, 2}, { 1, 2} }, .offset = {-1, 0} }, // 90
        { .set = { {-1, 1}, { 0, 0}, { 0, 0}, { 0, 0} }, .reset = { { 1, 0}, { 2, 1}, { 2, 1}, { 2, 1} }, .offset = {-1, 0} }, // 180
        { .set = { {-1, 0}, {-1, 1}, {-1, 2}, {-1, 2} }, .reset = { { 0, 0}, { 0, 2}, { 1, 1}, { 1, 1} }, .offset = {-1, 0} }, // 270
      },
      {
        // move right
        { .set = { { 3, 0}, { 2, 1}, { 2, 1}, { 2, 1} }, .reset = { { 0, 0}, { 1, 1}, { 1, 1}, { 1, 1} }, .offset = { 1, 0} }, // 0
        { .set = { { 2, 0}, { 2, 1}, { 2, 2}, { 2, 2} }, .reset = { { 0, 1}, { 1, 0}, { 1, 2}, { 1, 2} }, .offset = { 1, 0} }, // 90
        { .set = { { 3, 1}, { 2, 0}, { 2, 0}, { 2, 0} }, .reset = { { 0, 0}, { 0, 1}, { 1, 0}, { 1, 0} }, .offset = { 1, 0} }, // 180
        { .set = { { 1, 0}, { 1, 2}, { 2, 1}, { 2, 1} }, .reset = { { 0, 0}, { 0, 1}, { 0, 2}, { 0, 2} }, .offset = { 1, 0} }, // 270
      },
      {
        // rotate left
        { .set = { { 1,-1}, { 1,-1}, { 1,-1}, { 1,-1} }, .reset = { { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0} }, .offset = { 1,-1} }, // 0
        { .set = { { 2, 1}, { 2, 1}, { 2, 1}, { 2, 1} }, .reset = { { 1, 0}, { 1, 0}, { 1, 0}, { 1, 0} }, .offset = { 0, 1} }, // 90
        { .set = { { 1, 2}, { 1, 2}, { 1, 2}, { 1, 2} }, .reset = { { 2, 1}, { 2, 1}, { 2, 1}, { 2, 1} }, .offset = { 0, 0} }, // 180
        { .set = { {-1, 1}, {-1, 1}, {-1, 1}, {-1, 1} }, .reset = { { 0, 2}, { 0, 2}, { 0, 2}, { 0, 2} }, .offset = {-1, 0} }, // 270
      },
      {
        // rotate right
        { .set = { { 1,-1}, { 1,-1}, { 1,-1}, { 1,-1} }, .reset = { { 2, 0}, { 2, 0}, { 2, 0}, { 2, 0} }, .offset = { 0,-1} }, // 0
        { .set = { { 2, 1}, { 2, 1}, { 2, 1}, { 2, 1} }, .reset = { { 1, 2}, { 1, 2}, { 1, 2}, { 1, 2} }, .offset = { 0, 0} }, // 90
        { .set = { { 1, 2}, { 1, 2}, { 1, 2}, { 1, 2} }, .reset = { { 0, 1}, { 0, 1}, { 0, 1}, { 0, 1} }, .offset = { 1, 0} }, // 180
        { .set = { {-1, 1}, {-1, 1}, {-1, 1}, {-1, 1} }, .reset = { { 0, 0}, { 0, 0}, { 0, 0}, { 0, 0} }, .offset = {-1, 1} }, // 270
      },
    }
  },
  { // Z
    .color = _red,
    .nullRotation = 0,
    .draw = { { 0, 0}, { 1, 0}, { 1, 1}, { 2, 1} },
    .motion = {
      {
        // move down
        { .set = { { 0, 1}, { 1, 2}, { 2, 2}, { 2, 2} }, .reset = { { 0, 0}, { 1, 0}, { 2, 1}, { 2, 1} }, .offset = { 0, 1} }, // 0
        { .set = { { 1, 2}, { 0, 3}, { 0, 3}, { 0, 3} }, .reset = { { 1, 0}, { 0, 1}, { 0, 1}, { 0, 1} }, .offset = { 0, 1} }, // 90
        { .set = { { 0, 1}, { 1, 2}, { 2, 2}, { 2, 2} }, .reset = { { 0, 0}, { 1, 0}, { 2, 1}, { 2, 1} }, .offset = { 0, 1} }, // 180
        { .set = { { 1, 2}, { 0, 3}, { 0, 3}, { 0, 3} }, .reset = { { 1, 0}, { 0, 1}, { 0, 1}, { 0, 1} }, .offset = { 0, 1} }, // 270
      },
      {
        // move left
        { .set = { {-1, 0}, { 0, 1}, { 0, 1}, { 0, 1} }, .reset = { { 1, 0}, { 2, 1}, { 2, 1}, { 2, 1} }, .offset = {-1, 0} }, // 0
        { .set = { {-1, 1}, {-1, 2}, { 0, 0}, { 0, 0} }, .reset = { { 1, 0}, { 1, 1}, { 0, 2}, { 0, 2} }, .offset = {-1, 0} }, // 90
        { .set = { {-1, 0}, { 0, 1}, { 0, 1}, { 0, 1} }, .reset = { { 1, 0}, { 2, 1}, { 2, 1}, { 2, 1} }, .offset = {-1, 0} }, // 180
        { .set = { {-1, 1}, {-1, 2}, { 0, 0}, { 0, 0} }, .reset = { { 1, 0}, { 1, 1}, { 0, 2}, { 0, 2} }, .offset = {-1, 0} }, // 270
      },
      {
        // move right
        { .set = { { 3, 1}, { 2, 0}, { 2, 0}, { 2, 0} }, .reset = { { 0, 0}, { 1, 1}, { 1, 1}, { 1, 1} }, .offset = { 1, 0} }, // 0
        { .set = { { 2, 0}, { 2, 1}, { 1, 2}, { 1, 2} }, .reset = { { 0, 1}, { 0, 2}, { 1, 0}, { 1, 0} }, .offset = { 1, 0} }, // 90
        { .set = { { 3, 1}, { 2, 0}, { 2, 0}, { 2, 0} }, .reset = { { 0, 0}, { 1, 1}, { 1, 1}, { 1, 1} }, .offset = { 1, 0} }, // 180
        { .set = { { 2, 0}, { 2, 1}, { 1, 2}, { 1, 2} }, .reset = { { 0, 1}, { 0, 2}, { 1, 0}, { 1, 0} }, .offset = { 1, 0} }, // 270
      },
      {
        // rotate left
        { .set = { { 1,-1}, { 0, 1}, { 0, 1}, { 0, 1} }, .reset = { { 2, 1}, { 1, 1}, { 1, 1}, { 1, 1} }, .offset = { 0,-1} }, // 0
        { .set = { { 0, 0}, { 2, 1}, { 2, 1}, { 2, 1} }, .reset = { { 0, 2}, { 0, 1}, { 0, 1}, { 0, 1} }, .offset = { 0, 0} }, // 90
        { .set = { { 1,-1}, { 0, 1}, { 0, 1}, { 0, 1} }, .reset = { { 2, 1}, { 1, 1}, { 1, 1}, { 1, 1} }, .offset = { 0,-1} }, // 180
        { .set = { { 0, 0}, { 2, 1}, { 2, 1}, { 2, 1} }, .reset = { { 0, 2}, { 0, 1}, { 0, 1}, { 0, 1} }, .offset = { 0, 0} }, // 270
      },
      {
        // rotate right
        { .set = { { 1,-1}, { 0, 1}, { 0, 1}, { 0, 1} }, .reset = { { 2, 1}, { 1, 1}, { 1, 1}, { 1, 1} }, .offset = { 0,-1} }, // 0
        { .set = { { 0, 0}, { 2, 1}, { 2, 1}, { 2, 1} }, .reset = { { 0, 2}, { 0, 1}, { 0, 1}, { 0, 1} }, .offset = { 0, 0} }, // 90
        { .set = { { 1,-1}, { 0, 1}, { 0, 1}, { 0, 1} }, .reset = { { 2, 1}, { 1, 1}, { 1, 1}, { 1, 1} }, .offset = { 0,-1} }, // 180
        { .set = { { 0, 0}, { 2, 1}, { 2, 1}, { 2, 1} }, .reset = { { 0, 2}, { 0, 1}, { 0, 1}, { 0, 1} }, .offset = { 0, 0} }, // 270
      },
    }
  },
  { // S
    .color = _green,
    .nullRotation = 0,
    .draw = { { 0, 1}, { 1, 1}, { 1, 0}, { 2, 0} },
    .motion = {
      {
        // move down
        { .set = { { 0, 2}, { 1, 2}, { 2, 1}, { 2, 1} }, .reset = { { 0, 1}, { 1, 0}, { 2, 0}, { 2, 0} }, .offset = { 0, 1} }, // 0
        { .set = { { 0, 2}, { 1, 3}, { 1, 3}, { 1, 3} }, .reset = { { 0, 0}, { 1, 1}, { 1, 1}, { 1, 1} }, .offset = { 0, 1} }, // 90
        { .set = { { 0, 2}, { 1, 2}, { 2, 1}, { 2, 1} }, .reset = { { 0, 1}, { 1, 0}, { 2, 0}, { 2, 0} }, .offset = { 0, 1} }, // 180
        { .set = { { 0, 2}, { 1, 3}, { 1, 3}, { 1, 3} }, .reset = { { 0, 0}, { 1, 1}, { 1, 1}, { 1, 1} }, .offset = { 0, 1} }, // 270
      },
      {
        // move left
        { .set = { { 0, 0}, {-1, 1}, {-1, 1}, {-1, 1} }, .reset = { { 2, 0}, { 1, 1}, { 1, 1}, { 1, 1} }, .offset = {-1, 0} }, // 0
        { .set = { {-1, 0}, {-1, 1}, { 0, 2}, { 0, 2} }, .reset = { { 0, 0}, { 1, 1}, { 1, 2}, { 1, 2} }, .offset = {-1, 0} }, // 90
        { .set = { { 0, 0}, {-1, 1}, {-1, 1}, {-1, 1} }, .reset = { { 2, 0}, { 1, 1}, { 1, 1}, { 1, 1} }, .offset = {-1, 0} }, // 180
        { .set = { {-1, 0}, {-1, 1}, { 0, 2}, { 0, 2} }, .reset = { { 0, 0}, { 1, 1}, { 1, 2}, { 1, 2} }, .offset = {-1, 0} }, // 270
      },
      {
        // move right
        { .set = { { 2, 1}, { 3, 0}, { 3, 0}, { 3, 0} }, .reset = { { 1, 0}, { 0, 1}, { 0, 1}, { 0, 1} }, .offset = { 1, 0} }, // 0
        { .set = { { 1, 0}, { 2, 1}, { 2, 2}, { 2, 2} }, .reset = { { 0, 0}, { 0, 1}, { 1, 2}, { 1, 2} }, .offset = { 1, 0} }, // 90
        { .set = { { 2, 1}, { 3, 0}, { 3, 0}, { 3, 0} }, .reset = { { 1, 0}, { 0, 1}, { 0, 1}, { 0, 1} }, .offset = { 1, 0} }, // 180
        { .set = { { 1, 0}, { 2, 1}, { 2, 2}, { 2, 2} }, .reset = { { 0, 0}, { 0, 1}, { 1, 2}, { 1, 2} }, .offset = { 1, 0} }, // 270
      },
      {
        // rotate left
        { .set = { { 0, 0}, { 0,-1}, { 0,-1}, { 0,-1} }, .reset = { { 0, 1}, { 2, 0}, { 2, 0}, { 2, 0} }, .offset = { 0,-1} }, // 0
        { .set = { { 1, 0}, { 2, 0}, { 2, 0}, { 2, 0} }, .reset = { { 0, 0}, { 1, 2}, { 1, 2}, { 1, 2} }, .offset = { 0, 0} }, // 90
        { .set = { { 0, 0}, { 0,-1}, { 0,-1}, { 0,-1} }, .reset = { { 0, 1}, { 2, 0}, { 2, 0}, { 2, 0} }, .offset = { 0,-1} }, // 180
        { .set = { { 1, 0}, { 2, 0}, { 2, 0}, { 2, 0} }, .reset = { { 0, 0}, { 1, 2}, { 1, 2}, { 1, 2} }, .offset = { 0, 0} }, // 270
      },
      {
        // rotate right
        { .set = { { 0, 0}, { 0,-1}, { 0,-1}, { 0,-1} }, .reset = { { 0, 1}, { 2, 0}, { 2, 0}, { 2, 0} }, .offset = { 0,-1} }, // 0
        { .set = { { 1, 0}, { 2, 0}, { 2, 0}, { 2, 0} }, .reset = { { 0, 0}, { 1, 2}, { 1, 2}, { 1, 2} }, .offset = { 0, 0} }, // 90
        { .set = { { 0, 0}, { 0,-1}, { 0,-1}, { 0,-1} }, .reset = { { 0, 1}, { 2, 0}, { 2, 0}, { 2, 0} }, .offset = { 0,-1} }, // 180
        { .set = { { 1, 0}, { 2, 0}, { 2, 0}, { 2, 0} }, .reset = { { 0, 0}, { 1, 2}, { 1, 2}, { 1, 2} }, .offset = { 0, 0} }, // 270
      },
    }
  },
  { // L
    .color = _orange,
    .nullRotation = 0,
    .draw = { { 0, 0}, { 0, 1}, { 0, 2}, { 1, 2} },
    .motion = {
      {
        // move down
        { .set = { { 0, 3}, { 1, 3}, { 1, 3}, { 1, 3} }, .reset = { { 0, 0}, { 1, 2}, { 1, 2}, { 1, 2} }, .offset = { 0, 1} }, // 0
        { .set = { { 1, 1}, { 2, 1}, { 0, 2}, { 0, 2} }, .reset = { { 0, 0}, { 1, 0}, { 2, 0}, { 2, 0} }, .offset = { 0, 1} }, // 90
        { .set = { { 0, 1}, { 1, 3}, { 1, 3}, { 1, 3} }, .reset = { { 0, 0}, { 1, 0}, { 1, 0}, { 1, 0} }, .offset = { 0, 1} }, // 180
        { .set = { { 0, 2}, { 1, 2}, { 2, 2}, { 2, 2} }, .reset = { { 2, 0}, { 0, 1}, { 1, 1}, { 1, 1} }, .offset = { 0, 1} }, // 270
      },
      {
        // move left
        { .set = { {-1, 0}, {-1, 1}, {-1, 2}, {-1, 2} }, .reset = { { 0, 0}, { 0, 1}, { 1, 2}, { 0, 0} }, .offset = {-1, 0} }, // 0
        { .set = { {-1, 0}, {-1, 1}, {-1, 1}, {-1, 1} }, .reset = { { 0, 1}, { 2, 0}, { 2, 0}, { 2, 0} }, .offset = {-1, 0} }, // 90
        { .set = { { 0, 1}, { 0, 2}, {-1, 0}, {-1, 0} }, .reset = { { 1, 0}, { 1, 1}, { 1, 2}, { 1, 2} }, .offset = {-1, 0} }, // 180
        { .set = { {-1, 1}, { 1, 0}, { 1, 0}, { 1, 0} }, .reset = { { 2, 0}, { 2, 1}, { 2, 1}, { 2, 1} }, .offset = {-1, 0} }, // 270
      },
      {
        // move right
        { .set = { { 1, 0}, { 1, 1}, { 2, 2}, { 2, 2} }, .reset = { { 0, 0}, { 0, 1}, { 0, 2}, { 0, 2} }, .offset = { 1, 0} }, // 0
        { .set = { { 1, 1}, { 3, 0}, { 3, 0}, { 3, 0} }, .reset = { { 0, 0}, { 0, 1}, { 0, 1}, { 0, 1} }, .offset = { 1, 0} }, // 90
        { .set = { { 2, 0}, { 2, 1}, { 2, 2}, { 2, 2} }, .reset = { { 0, 0}, { 1, 1}, { 1, 2}, { 1, 2} }, .offset = { 1, 0} }, // 180
        { .set = { { 3, 0}, { 3, 1}, { 3, 1}, { 3, 1} }, .reset = { { 0, 1}, { 2, 0}, { 2, 0}, { 2, 0} }, .offset = { 1, 0} }, // 270
      },
      {
        // rotate left
        { .set = { {-1, 2}, {-2, 2}, {-2, 2}, {-2, 2} }, .reset = { { 0, 0}, { 1, 2}, { 1, 2}, { 1, 2} }, .offset = {-2, 1} }, // 0
        { .set = { { 0,-1}, { 0,-2}, { 0,-2}, { 0,-2} }, .reset = { { 0, 1}, { 2, 0}, { 2, 0}, { 2, 0} }, .offset = { 0,-2} }, // 90
        { .set = { { 2, 0}, { 3, 0}, { 3, 0}, { 3, 0} }, .reset = { { 0, 0}, { 1, 2}, { 1, 2}, { 1, 2} }, .offset = { 1, 0} }, // 180
        { .set = { { 2, 2}, { 2, 3}, { 2, 3}, { 2, 3} }, .reset = { { 0, 1}, { 2, 0}, { 2, 0}, { 2, 0} }, .offset = { 1, 1} }, // 270
      },
      {
        // rotate right
        { .set = { { 0, 3}, { 2, 2}, { 2, 2}, { 2, 2} }, .reset = { { 0, 0}, { 0, 1}, { 0, 1}, { 0, 1} }, .offset = { 0, 2} }, // 0
        { .set = { {-1, 0}, { 0, 2}, { 0, 2}, { 0, 2} }, .reset = { { 1, 0}, { 2, 0}, { 2, 0}, { 2, 0} }, .offset = {-1, 0} }, // 90
        { .set = { {-1, 0}, { 1,-1}, { 1,-1}, { 1,-1} }, .reset = { { 1, 1}, { 1, 2}, { 1, 2}, { 1, 2} }, .offset = {-1,-1} }, // 180
        { .set = { { 2,-1}, { 3, 1}, { 3, 1}, { 3, 1} }, .reset = { { 0, 1}, { 1, 1}, { 1, 1}, { 1, 1} }, .offset = { 2,-1} }, // 270
      },
    }
  },
  { // J
    .color = _blue,
    .nullRotation = 0,
    .draw = { { 0, 2}, { 1, 0}, { 1, 1}, { 1, 2} },
    .motion = {
      {
        // move down
        { .set = { { 0, 3}, { 1, 3}, { 1, 3}, { 1, 3} }, .reset = { { 0, 2}, { 1, 0}, { 1, 0}, { 1, 0} }, .offset = { 0, 1} }, // 0
        { .set = { { 0, 2}, { 1, 2}, { 2, 2}, { 2, 2} }, .reset = { { 0, 0}, { 1, 1}, { 2, 1}, { 2, 1} }, .offset = { 0, 1} }, // 90
        { .set = { { 0, 3}, { 1, 1}, { 1, 1}, { 1, 1} }, .reset = { { 0, 0}, { 1, 0}, { 1, 0}, { 1, 0} }, .offset = { 0, 1} }, // 180
        { .set = { { 0, 1}, { 1, 1}, { 2, 2}, { 2, 2} }, .reset = { { 0, 0}, { 1, 0}, { 2, 0}, { 2, 0} }, .offset = { 0, 1} }, // 270
      },
      {
        // move left
        { .set = { { 0, 0}, { 0, 1}, {-1, 2}, {-1, 2} }, .reset = { { 1, 0}, { 1, 1}, { 1, 2}, { 1, 2} }, .offset = {-1, 0} }, // 0
        { .set = { {-1, 0}, {-1, 1}, {-1, 1}, {-1, 1} }, .reset = { { 0, 0}, { 2, 1}, { 2, 1}, { 2, 1} }, .offset = {-1, 0} }, // 90
        { .set = { {-1, 0}, {-1, 1}, {-1, 2}, {-1, 2} }, .reset = { { 1, 0}, { 0, 1}, { 0, 2}, { 0, 2} }, .offset = {-1, 0} }, // 180
        { .set = { {-1, 0}, { 1, 1}, { 1, 1}, { 1, 1} }, .reset = { { 2, 0}, { 2, 1}, { 2, 1}, { 2, 1} }, .offset = {-1, 0} }, // 270
      },
      {
        // move right
        { .set = { { 2, 0}, { 2, 1}, { 2, 2}, { 2, 2} }, .reset = { { 1, 0}, { 1, 1}, { 0, 2}, { 0, 2} }, .offset = { 1, 0} }, // 0
        { .set = { { 1, 0}, { 3, 1}, { 3, 1}, { 3, 1} }, .reset = { { 0, 0}, { 0, 1}, { 0, 1}, { 0, 1} }, .offset = { 1, 0} }, // 90
        { .set = { { 1, 1}, { 1, 2}, { 2, 0}, { 2, 0} }, .reset = { { 0, 0}, { 0, 1}, { 0, 2}, { 0, 2} }, .offset = { 1, 0} }, // 180
        { .set = { { 3, 0}, { 3, 1}, { 3, 1}, { 3, 1} }, .reset = { { 0, 0}, { 2, 1}, { 2, 1}, { 2, 1} }, .offset = { 1, 0} }, // 270
      },
      {
        // rotate left
        { .set = { { 1, 3}, {-1, 2}, {-1, 2}, {-1, 2} }, .reset = { { 1, 0}, { 1, 1}, { 0, 0}, { 0, 0} }, .offset = {-1, 2} }, // 0
        { .set = { {-1, 1}, { 0,-1}, { 0,-1}, { 0,-1} }, .reset = { { 1, 1}, { 2, 1}, { 2, 1}, { 2, 1} }, .offset = {-1,-1} }, // 90
        { .set = { { 2, 0}, { 0,-1}, { 0,-1}, { 0,-1} }, .reset = { { 0, 1}, { 0, 2}, { 0, 2}, { 0, 2} }, .offset = { 0,-1} }, // 180
        { .set = { { 2, 2}, { 3, 0}, { 3, 0}, { 3, 0} }, .reset = { { 0, 0}, { 1, 0}, { 1, 0}, { 1, 0} }, .offset = { 2, 0} }, // 270
      },
      {
        // rotate right
        { .set = { { 2, 2}, { 3, 2}, { 3, 2}, { 3, 2} }, .reset = { { 1, 0}, { 0, 2}, { 0, 2}, { 0, 2} }, .offset = { 1, 1} }, // 0
        { .set = { { 0, 2}, { 0, 3}, { 0, 3}, { 0, 3} }, .reset = { { 0, 0}, { 2, 1}, { 2, 1}, { 2, 1} }, .offset = { 0, 1} }, // 90
        { .set = { {-1, 0}, {-2, 0}, {-2, 0}, {-2, 0} }, .reset = { { 1, 0}, { 0, 2}, { 0, 2}, { 0, 2} }, .offset = {-2, 0} }, // 180
        { .set = { { 2,-1}, { 2,-2}, { 2,-2}, { 2,-2} }, .reset = { { 0, 0}, { 2, 1}, { 2, 1}, { 2, 1} }, .offset = { 1,-2} }, // 270
      },
    }
  },
};

const orientation_t nextOrientation[5][4] = { // 5 = number of directions to move, 4 = number of orientation a stone can have
  { e_Keep, e_Keep, e_Keep, e_Keep }, // move down,  current orientation: 0, 90, 180, 270
  { e_Keep, e_Keep, e_Keep, e_Keep }, // move left
  { e_Keep, e_Keep, e_Keep, e_Keep }, // move right
  { e_270,  e_0,    e_90,   e_180  }, // rotate left
  { e_90,   e_180,  e_270,  e_0    }  // rotate right
};

stone_t stone;
shape_t nextShape;

static shape_t randomNextShape() {
  return ((shape_t[]){ e_I, e_O, e_T, e_Z, e_S, e_L, e_J })[myRandGet() % e_ShapeInvalid];
}

void shapesInit() {
  stone.shape = e_ShapeInvalid;
  nextShape = randomNextShape();
}

void stoneCreate() {
  stone.shape = nextShape;
  nextShape = randomNextShape();
  stone.orientation = e_0;
  stone.x = 4;
  stone.y = 0;
  stone.locked = false;
}

void stoneLock() {
  stone.locked = true;
}

uint8_t stoneIsValid() {
  return stone.shape != e_ShapeInvalid;
}

// all of them return 1 in case of success and 0 in case of error
static uint8_t move(direction_t direction) {
  // if this is a rotation and the shape is marked with nullRotation (just the O), do nothing
  // and return success
  if (motions[stone.shape].nullRotation && (direction == e_RotateLeft || direction == e_RotateRight)) {
    return 1;
  }

  // if the stone is already locked, do nothing
  if (stone.locked) {
    return 0;
  }

  // check whether the pixels to move to are free
  if (canvasIsPixelFree(stone.x + motions[stone.shape].motion[direction][stone.orientation].set[0].x, 
                        stone.y + motions[stone.shape].motion[direction][stone.orientation].set[0].y) &&
      canvasIsPixelFree(stone.x + motions[stone.shape].motion[direction][stone.orientation].set[1].x, 
                        stone.y + motions[stone.shape].motion[direction][stone.orientation].set[1].y) &&
      canvasIsPixelFree(stone.x + motions[stone.shape].motion[direction][stone.orientation].set[2].x, 
                        stone.y + motions[stone.shape].motion[direction][stone.orientation].set[2].y) &&
      canvasIsPixelFree(stone.x + motions[stone.shape].motion[direction][stone.orientation].set[3].x, 
                        stone.y + motions[stone.shape].motion[direction][stone.orientation].set[3].y)) {
    // if so, reset the pixels the shape moves away from
    canvasSetPixel(stone.x + motions[stone.shape].motion[direction][stone.orientation].reset[0].x, 
                   stone.y + motions[stone.shape].motion[direction][stone.orientation].reset[0].y, 
                   _off);
    canvasSetPixel(stone.x + motions[stone.shape].motion[direction][stone.orientation].reset[1].x, 
                   stone.y + motions[stone.shape].motion[direction][stone.orientation].reset[1].y, 
                   _off);
    canvasSetPixel(stone.x + motions[stone.shape].motion[direction][stone.orientation].reset[2].x, 
                   stone.y + motions[stone.shape].motion[direction][stone.orientation].reset[2].y, 
                   _off);
    canvasSetPixel(stone.x + motions[stone.shape].motion[direction][stone.orientation].reset[3].x, 
                   stone.y + motions[stone.shape].motion[direction][stone.orientation].reset[3].y, 
                   _off);
    // and set the pixels the shape moves to to the shape's color
    canvasSetPixel(stone.x + motions[stone.shape].motion[direction][stone.orientation].set[0].x, 
                   stone.y + motions[stone.shape].motion[direction][stone.orientation].set[0].y, 
                   motions[stone.shape].color);
    canvasSetPixel(stone.x + motions[stone.shape].motion[direction][stone.orientation].set[1].x, 
                   stone.y + motions[stone.shape].motion[direction][stone.orientation].set[1].y, 
                   motions[stone.shape].color);
    canvasSetPixel(stone.x + motions[stone.shape].motion[direction][stone.orientation].set[2].x, 
                   stone.y + motions[stone.shape].motion[direction][stone.orientation].set[2].y, 
                   motions[stone.shape].color);
    canvasSetPixel(stone.x + motions[stone.shape].motion[direction][stone.orientation].set[3].x, 
                   stone.y + motions[stone.shape].motion[direction][stone.orientation].set[3].y, 
                   motions[stone.shape].color);
    // set the new origin of the shape
    stone.x += motions[stone.shape].motion[direction][stone.orientation].offset.x;
    stone.y += motions[stone.shape].motion[direction][stone.orientation].offset.y;
    // set the new orientation of the shape, if required
    stone.orientation = (nextOrientation[direction][stone.orientation] == e_Keep) ? 
                        stone.orientation : 
                        nextOrientation[direction][stone.orientation];
    return 1;
  }
  return 0;
}

void nextStoneDraw() {
  miniCanvasClear();
  miniCanvasSetPixel(motions[nextShape].draw[0].x, 
                     motions[nextShape].draw[0].y, 
                     motions[nextShape].color);
  miniCanvasSetPixel(motions[nextShape].draw[1].x, 
                     motions[nextShape].draw[1].y, 
                     motions[nextShape].color);
  miniCanvasSetPixel(motions[nextShape].draw[2].x, 
                     motions[nextShape].draw[2].y, 
                     motions[nextShape].color);
  miniCanvasSetPixel(motions[nextShape].draw[3].x, 
                     motions[nextShape].draw[3].y, 
                     motions[nextShape].color);
}

static void stoneJustDraw(uint8_t x, uint8_t y, shape_t shape) {
  canvasSetPixel(x + motions[shape].draw[0].x, 
                 y + motions[shape].draw[0].y, 
                 motions[shape].color);
  canvasSetPixel(x + motions[shape].draw[1].x, 
                 y + motions[shape].draw[1].y, 
                 motions[shape].color);
  canvasSetPixel(x + motions[shape].draw[2].x, 
                 y + motions[shape].draw[2].y, 
                 motions[shape].color);
  canvasSetPixel(x + motions[shape].draw[3].x, 
                 y + motions[shape].draw[3].y, 
                 motions[shape].color);
}

uint8_t stoneDraw() { 
  nextStoneDraw();

  uint8_t res = 0;
  // check if the pixels the shape should be drawn at are free
  if (canvasIsPixelFree(stone.x + motions[stone.shape].draw[0].x, 
                        stone.y + motions[stone.shape].draw[0].y) &&
      canvasIsPixelFree(stone.x + motions[stone.shape].draw[1].x, 
                        stone.y + motions[stone.shape].draw[1].y) &&
      canvasIsPixelFree(stone.x + motions[stone.shape].draw[2].x, 
                        stone.y + motions[stone.shape].draw[2].y) &&
      canvasIsPixelFree(stone.x + motions[stone.shape].draw[3].x, 
                        stone.y + motions[stone.shape].draw[3].y)) {
    // if so, draw the shape
    stoneJustDraw(stone.x, stone.y, stone.shape);
    res = 1;
  }
  return res;
}

void stoneDrawConfigPattern() {
  stoneJustDraw(1, 0, e_I);
  stoneJustDraw(3, 4, e_O);
  stoneJustDraw(4, 7, e_T);
  stoneJustDraw(5, 10, e_Z);
  stoneJustDraw(1, 12, e_S);
  stoneJustDraw(5, 15, e_L);
  stoneJustDraw(1, 17, e_J);
}

uint8_t stoneMoveDown() {
  return move(e_MoveDown);
}

uint8_t stoneMoveLeft() {
  return move(e_MoveLeft);
}

uint8_t stoneMoveRight() {
  return move(e_MoveRight);
}

uint8_t stoneRotateLeft() {
  return move(e_RotateLeft);
}

uint8_t stoneRotateRight() {
  return move(e_RotateRight);
}







