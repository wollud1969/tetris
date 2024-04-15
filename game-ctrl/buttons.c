#include <stddef.h>
#include <stdint.h>
#include <msp430g2553.h>

#include "buttons.h"
#include "scheduler.h"
#include "shapes.h"
#include "canvas.h"
#include "sound.h"


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
  static uint32_t unmuteTimestamp;
  uint32_t currentTimestamp = getSeconds();
  static bool unmuteFlag = false;


  if (! stoneIsValid()) {
    // don't do anything, the stone has not been initialized
    return;
  }

  uint8_t buttonPressed = 0;

  if (buttonsMoveLeftPressed()) {
    stoneMoveLeft();
    soundCtrl(e_SOUND_STONE_MOVE_LEFT);
    buttonPressed = 1;
  }
  if (buttonsMoveRightPressed()) {
    stoneMoveRight();
    soundCtrl(e_SOUND_STONE_MOVE_RIGHT);
    buttonPressed = 1;
  }
  if (buttonsRotateLeftPressed()) {
    stoneRotateLeft();
    soundCtrl(e_SOUND_STONE_ROTATE_LEFT);
    buttonPressed = 1;
  }
  if (buttonsRotateRightPressed()) {
    stoneRotateRight();
    soundCtrl(e_SOUND_STONE_ROTATE_RIGHT);
    buttonPressed = 1;
  }
  if (buttonsMoveDownPressed()) {
    stoneMoveDown();
    soundCtrl(e_SOUND_STONE_MOVE_DOWN);
    buttonPressed = 1;
  }

  if (buttonPressed == 1) {
    canvasShow();

    if (! unmuteFlag) {
      soundCtrl(e_SOUND_UNMUTE);
      unmuteFlag = true;
    }
    unmuteTimestamp = currentTimestamp;
  }

  if (unmuteFlag && (unmuteTimestamp + MUTE_DELAY < currentTimestamp)) {
    soundCtrl(e_SOUND_MUTE);
    unmuteFlag = false;
  }
}

void buttonsInit() {
  P2DIR &= ~(BIT0|BIT1|BIT2|BIT3|BIT4);

  schAdd(buttonsExec, NULL, 0, 25);
}

