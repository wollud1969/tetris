#include "stddef.h"
#include "stdint.h"

#include "game.h"
#include "scheduler.h"
#include "shapes.h"
#include "canvas.h"
#include "../rgb-driver/colors.h"
#include "display.h"
#include "sound.h"
#include "eeprom.h"
#include "buttons.h"


#define GAME_CYCLE_TIME 50
#define GAMEOVER_DELAY 10
#define MAX_LEVEL 20


static uint8_t delayFactor(uint8_t level) {
  return MAX_LEVEL + 1 - level;
}

typedef enum { 
  e_Start, e_NewStone, e_Down, e_DownDelay, e_ClearRows,
  e_GameOver, e_GameOverFill, e_GameOverWipe, e_GameOverDelay 
} state_t;

void gameExec(void *handle) {
  static state_t state = e_Start;
  static uint8_t gameOverDelay;
  static uint8_t rowIndex;
  static uint8_t proceedDelay;
  static uint8_t level;
  static uint16_t filledLines;
  static uint16_t score;
  static bool newHighScoreAchieved;

  bool wipedLines = false;

// --- engine begin -------------------------------------------------------
  switch (state) {
// --- phase: game --------------------------------------------------------
    case e_Start:
      canvasClear();
      soundCtrl(SOUND_START);
      level = 1;
      filledLines = 0;
      score = 0;
      newHighScoreAchieved = false;
      state = e_NewStone;
      break;

    case e_NewStone:
      stoneCreate();
      if (stoneDraw()) {
        proceedDelay = delayFactor(level);
        state = e_DownDelay;
      } else {
        state = e_GameOver;
      }
      break;

    case e_DownDelay:
      proceedDelay--;
      if (proceedDelay == 0) {
        rowIndex = 0;
        state = e_Down;
      }
      break;

    case e_Down:
      if (! stoneMoveDown()) {
        soundCtrl(SOUND_LOCK);
        stoneLock();
        state = e_ClearRows;
      } else {
        proceedDelay = delayFactor(level);
        state = e_DownDelay;
      }
      break;

    case e_ClearRows:
      // clear filled lines
      for (uint8_t r = 0; r < CANVAS_HEIGHT; r++) {
        if (canvasIsRowFilled(r)) {
          score += level;
          if (score > eepromReadHighScore()) {
            newHighScoreAchieved = true;
            eepromWriteHighScore(score);
          }
          displaySetValue(score);
          canvasWipeRow(r);
          canvasShow();
          wipedLines = true;
          filledLines += 1;
        }
      }

      if (wipedLines) {
        soundCtrl(SOUND_PLING);
      }

      if (wipedLines && (filledLines > 0) && ((filledLines % 10) == 0)) {
        if (level < MAX_LEVEL) {
          level += 1;
        }
        soundCtrl(SOUND_FANFARE); 
      }

      state = e_NewStone;
      break;

// --- phase: game over ---------------------------------------------------
    case e_GameOver:
      soundCtrl(SOUND_GAMEOVER);
      rowIndex = CANVAS_HEIGHT;
      state = e_GameOverFill;
      break;

    case e_GameOverFill:
      rowIndex--;
      canvasFillRow(rowIndex, newHighScoreAchieved ? _green : _red);
      if (rowIndex == 0) {
        state = e_GameOverWipe;
      }
      break;

    case e_GameOverWipe:
      canvasWipeRow(rowIndex);
      rowIndex++;
      if (rowIndex == CANVAS_HEIGHT) {
        gameOverDelay = GAMEOVER_DELAY;
        state = e_GameOverDelay;
      }
      break;

    case e_GameOverDelay:
      gameOverDelay--;
      if (gameOverDelay == 0) {
        state = e_Start;
      }
      break;
  }
// --- engine end ---------------------------------------------------------

  canvasShow();

  if (isGameActive()) {
    displaySetValue(score);
  } else {
    displaySetValue(eepromReadHighScore());
  }
}

void gameInit() {
  schAdd(gameExec, NULL, 0, GAME_CYCLE_TIME);
}

