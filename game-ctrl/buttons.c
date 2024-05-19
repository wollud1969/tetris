#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <msp430g2553.h>

#include "buttons.h"
#include "scheduler.h"
#include "shapes.h"
#include "canvas.h"
#include "sound.h"


bool mutedFlag = true;

static uint8_t buttonsMoveLeftPressed() {
  static uint8_t last = 0;
  uint8_t current = (P2IN & BIT4);
  uint8_t res = (current != 0) && (current != last);
  last = current;
  return res;
}

bool buttonsConfig1Pressed() {
  return buttonsMoveLeftPressed();
}

static uint8_t buttonsMoveRightPressed() {
  static uint8_t last = 0;
  uint8_t current = (P2IN & BIT0);
  uint8_t res = (current != 0) && (current != last);
  last = current;
  return res;
}

bool buttonsConfig4Pressed() {
  return buttonsMoveRightPressed();
}

static uint8_t buttonsRotateLeftPressed() {
  static uint8_t last = 0;
  uint8_t current = (P2IN & BIT3);
  uint8_t res = (current != 0) && (current != last);
  last = current;
  return res;
}

bool buttonsConfig2Pressed() {
  return buttonsRotateLeftPressed();
}

static uint8_t buttonsRotateRightPressed() {
  static uint8_t last = 0;
  uint8_t current = (P2IN & BIT1);
  uint8_t res = (current != 0) && (current != last);
  last = current;
  return res;
}

bool buttonsConfig3Pressed() {
  return buttonsRotateRightPressed();
}


static uint8_t buttonsMoveDownPressed() {
  return P2IN & BIT2;
}

bool isConfigMode() {
  return (P2IN & BIT2);
}


void buttonsExec(void *handle) {
  static uint32_t unmuteTimestamp;
  uint32_t currentTimestamp = getSeconds();


  if (! stoneIsValid()) {
    // don't do anything, the stone has not been initialized
    return;
  }

  uint8_t buttonPressed = 0;

  if (buttonsMoveLeftPressed()) {
    stoneMoveLeft();
    soundCtrl(SOUND_MOTION);
    buttonPressed = 1;
  }
  if (buttonsMoveRightPressed()) {
    stoneMoveRight();
    soundCtrl(SOUND_MOTION);
    buttonPressed = 1;
  }
  if (buttonsRotateLeftPressed()) {
    stoneRotateLeft();
    soundCtrl(SOUND_MOTION);
    buttonPressed = 1;
  }
  if (buttonsRotateRightPressed()) {
    stoneRotateRight();
    soundCtrl(SOUND_MOTION);
    buttonPressed = 1;
  }
  if (buttonsMoveDownPressed()) {
    stoneMoveDown();
    soundCtrl(SOUND_MOTION);
    buttonPressed = 1;
  }

  if (buttonPressed == 1) {
    canvasShow();

    if (mutedFlag) {
      soundCtrl(SOUND_UNMUTE);
      mutedFlag = false;
    }
    unmuteTimestamp = currentTimestamp;
  }

  if ((! mutedFlag) && (unmuteTimestamp + MUTE_DELAY < currentTimestamp)) {
    soundCtrl(SOUND_MUTE);
    mutedFlag = true;
  }
}

void buttonsInit() {
  P2DIR &= ~(BIT0|BIT1|BIT2|BIT3|BIT4);
}

void buttonsStart() {
  schAdd(buttonsExec, NULL, 0, 25);
}

bool isGameActive() {
  return ! mutedFlag;
}

