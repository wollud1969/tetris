#ifndef _SHAPES_H_
#define _SHAPES_H_

#include <stdint.h>

void shapesInit();
void stoneCreate();
void stoneLock();
uint8_t stoneIsValid();
uint8_t stoneDraw();
uint8_t stoneMoveDown();
uint8_t stoneMoveLeft();
uint8_t stoneMoveRight();
uint8_t stoneRotateLeft();
uint8_t stoneRotateRight();

void stoneDrawConfigPattern();

#endif // _SHAPES_H_
