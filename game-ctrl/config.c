#include <stddef.h>
#include "config.h"
#include "canvas.h"
#include "../rgb-driver/colors.h"
#include "scheduler.h"
#include "buttons.h"
#include "eeprom.h"
#include "display.h"


typedef enum { e_Config_Flash, e_Config_ResetHighscore, e_Config_End } t_ConfigState;

static bool configChanged = false;

static void configHandleFlash() {
  if (buttonsConfig2Pressed()) {
    configChanged = true;
    uint8_t color = eepromReadFlashColor() + 1;
    if (color == _color_end) {
      color = 0;
    }
    canvasFillRow(CANVAS_HEIGHT-1, color);
    displaySetValue(color);
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

void (*configHandler[])(void) = { configHandleFlash, configHandleResetHighScore };


void configExec(void *handle) {
  static t_ConfigState configState = e_Config_Flash;

  if (buttonsConfig1Pressed()) {
    configState += 1;
    if (configState == e_Config_End) {
      configState = e_Config_Flash;
    }
    miniCanvasClear();
    canvasClear();

    miniCanvasSetPixel(configState, 0, _medium_red);
  }

  configHandler[configState]();

  if (configChanged) {
    miniCanvasSetPixel(0, 2, _medium_red);
    if (buttonsConfig4Pressed()) {
      eepromCommit();
      configChanged = false;
    }
  } else {
    miniCanvasSetPixel(0, 2, _medium_green);
  }


  canvasShow();
}


void configInit() {
  schAdd(configExec, NULL, 0, 25);
}
