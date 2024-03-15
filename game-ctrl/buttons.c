#include "stddef.h"
#include "stdint.h"

#include "buttons.h"
#include "PontCoopScheduler.h"
#include "shapes.h"
#include "canvas.h"
#include "led.h"


// TEST CODE
uint16_t counter;


static uint8_t buttonsMoveLeftPressed() {
  // -----------------------
  // TEST CODE
  //if (counter == 25) {
  //  ledGreenToggle();
  //  return 1;
  //}
  // -----------------------
  return 0;
}

static uint8_t buttonsMoveRightPressed() {
  return 0;
}

static uint8_t buttonsRotateLeftPressed() {
  // -----------------------
  // TEST CODE
  if (counter == 35) {
    ledGreenToggle();
    return 1;
  }
  // -----------------------
  return 0;
}

static uint8_t buttonsRotateRightPressed() {
  return 0;
}

void buttonsExec(void *handle) {
  if (! stoneIsValid()) {
    // don't do anything, the stone has not been initialized
    return;
  }

  // TEST CODE
  counter++;

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

  if (buttonPressed == 1) {
    canvasShow();
  }
}

void buttonsInit() {
  // TEST CODE
  counter = 0;

  schAdd(buttonsExec, NULL, 0, 100);
}

