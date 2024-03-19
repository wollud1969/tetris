#include <stddef.h>
#include <stdint.h>
#include <msp430g2553.h>

#include "buttons.h"
#include "scheduler.h"
#include "shapes.h"
#include "canvas.h"
#include "led.h"



static uint8_t buttonsMoveLeftPressed() {
  static uint8_t last = 0;
  uint8_t current = (P2IN & BIT4);
  uint8_t res = (current != 0) && (current != last);
  last = current;
  return res;
}

static uint8_t buttonsMoveRightPressed() {
  static uint8_t last = 0;
  uint8_t current = (P2IN & BIT0);
  uint8_t res = (current != 0) && (current != last);
  last = current;
  return res;
}

static uint8_t buttonsRotateLeftPressed() {
  static uint8_t last = 0;
  uint8_t current = (P2IN & BIT3);
  uint8_t res = (current != 0) && (current != last);
  last = current;
  return res;
}

static uint8_t buttonsRotateRightPressed() {
  static uint8_t last = 0;
  uint8_t current = (P2IN & BIT1);
  uint8_t res = (current != 0) && (current != last);
  last = current;
  return res;
}

static uint8_t buttonsMoveDownPressed() {
  return P2IN & BIT2;
}

void buttonsExec(void *handle) {
  if (! stoneIsValid()) {
    // don't do anything, the stone has not been initialized
    return;
  }

  uint8_t buttonPressed = 0;

  if (buttonsMoveLeftPressed()) {
    stoneMoveLeft();
    buttonPressed = 1;
  }
  if (buttonsMoveRightPressed()) {
    stoneMoveRight();
    buttonPressed = 1;
  }
  if (buttonsRotateLeftPressed()) {
    stoneRotateLeft();
    buttonPressed = 1;
  }
  if (buttonsRotateRightPressed()) {
    stoneRotateRight();
    buttonPressed = 1;
  }
  if (buttonsMoveDownPressed()) {
    stoneMoveDown();
    buttonPressed = 1;
  }

  if (buttonPressed == 1) {
    canvasShow();
  }
}

void buttonsInit() {
  P2DIR &= ~(BIT0|BIT1|BIT2|BIT3|BIT4);

  schAdd(buttonsExec, NULL, 0, 25);
}

