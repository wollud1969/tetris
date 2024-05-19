#include <stddef.h>
#include "config.h"
#include "canvas.h"
#include "../rgb-driver/colors.h"
#include "scheduler.h"
#include "buttons.h"
#include "eeprom.h"
#include "display.h"
#include "shapes.h"


static bool configChanged = false;

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

void (*configHandler[])(void) = { configHandleFlash, configHandleResetHighScore, configHandleBrightness };


void configExec(void *handle) {
  static uint8_t configState = 0;
  static uint8_t lastConfigState = 255;

  if (configState != lastConfigState) {
    lastConfigState = configState;

    miniCanvasClear();
    canvasClear();
    miniCanvasSetPixel(configState, 0, _red);
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
