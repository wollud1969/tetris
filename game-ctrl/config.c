#include <stddef.h>
#include "config.h"
#include "canvas.h"
#include "../rgb-driver/colors.h"
#include "scheduler.h"
#include "buttons.h"
#include "eeprom.h"
#include "display.h"
#include "shapes.h"
#include "sound.h"


static bool configChanged = false;
static bool muted = false;

static void configHandleFlash() {
  uint8_t color = eepromReadFlashColor();

  canvasFillRow(CANVAS_HEIGHT-1, color);
  displaySetValue(color);

  if (buttonsConfig2Pressed()) {
    configChanged = true;
    color += 1;
    if (color > _color_end) {
      color = 0;
    }
    eepromSetFlashColor(color);
  }
}

static void configHandleResetHighScore() {
  displaySetValue(eepromReadHighScore());

  if (buttonsConfig2Pressed()) {
    configChanged = true;
    eepromSetHighScore(0);
  }
}

static void configHandleResetGameCounter() {
  displaySetValue(eepromReadGameCounter());

  if (buttonsConfig2Pressed()) {
    configChanged = true;
    eepromClearGameCounter(0);
  }
}

static void configHandleBrightness() {
  displaySetValue(eepromReadBrightness());
  stoneDrawConfigPattern();

  if (buttonsConfig2Pressed()) {
    configChanged = true;
    uint8_t brightness = eepromReadBrightness() + 1;
    if (brightness > _brightness_shifts) {
      brightness = 0;
    }
    eepromSetBrightness(brightness);
  }
}

static void configHandleAmplitude() {
  displaySetValue(eepromReadAmplitude());
  if (muted) {
    muted = false;
    soundCtrl(SOUND_START);
    soundCtrl(SOUND_UNMUTE);
  }

  if (buttonsConfig2Pressed()) {
    configChanged = true;
    uint8_t amplitude = eepromReadAmplitude() + 1;
    if (amplitude > 15) {
      amplitude = 0;
    }
    eepromSetAmplitude(amplitude);
    soundCtrl(SOUND_COMMAND + SOUND_SUBCMD_AMPLITUDE + amplitude);
  }
}

void (*configHandler[])(void) = { 
  configHandleResetHighScore, 
  configHandleResetGameCounter, 
  configHandleFlash, 
  configHandleBrightness, 
  configHandleAmplitude 
};

void configExec(void *handle) {
  static uint8_t configState = 0;
  static uint8_t lastConfigState = 255;

  if (configState != lastConfigState) {
    lastConfigState = configState;

    miniCanvasClear();
    canvasClear();
    if (! muted) {
      muted = true;
      soundCtrl(SOUND_MUTE);
    }

    uint8_t row = configState / 3;
    uint8_t column = configState % 3;
    miniCanvasSetPixel(column, row, _red);
  }

  if (buttonsConfig1Pressed()) {
    configState += 1;
    if (configState >= sizeof(configHandler) / sizeof(configHandler[0])) {
      configState = 0;
    }
  }

  configHandler[configState]();

  if (configChanged) {
    miniCanvasSetPixel(0, 3, _red);
    if (buttonsConfig4Pressed()) {
      eepromCommit();
      configChanged = false;
    }
  } else {
    miniCanvasSetPixel(0, 3, _green);
  }

  canvasShow();
}


void configInit() {
  schAdd(configExec, NULL, 0, 100);
}
