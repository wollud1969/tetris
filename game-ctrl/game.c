// #define STATE_DEBUGGING

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


#define GAME_CYCLE_TIME 10
#define GAMEOVER_DELAY 10
#define MAX_LEVEL 100


static uint16_t delayFactor(uint16_t level) {
  return MAX_LEVEL + 1 - level;
}

typedef enum { 
  e_BootWait,
  e_Start, e_NewStone, e_Down, e_DownDelay, 
  e_ClearRowInit, e_ClearRowNext, e_ClearRowCheck, e_ClearRowFlash, e_ClearRowFlashDelay, e_ClearRowWipe,
  e_GameOver, e_GameOverFill, e_GameOverWipe, e_GameOverDelay 
} state_t;

void gameExec(void *handle) {
  static state_t state = e_BootWait;
  static uint16_t bootWaitTime = 2500 / GAME_CYCLE_TIME;
  static uint8_t gameOverDelay;
  static uint8_t rowIndex;
  static uint16_t proceedDelay;
  static uint16_t level;
  static uint16_t filledLines;
  static uint16_t score;
  static bool newHighScoreAchieved;

  static uint8_t clearCheckCnt;

#ifdef STATE_DEBUGGING
  displaySetValue(state);
#endif
// --- engine begin -------------------------------------------------------
  switch (state) {
    case e_BootWait:
      bootWaitTime -= 1;
      if (bootWaitTime == 0) {
        state = e_Start;
      }
      break;
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
        state = e_Down;
      }
      break;

    case e_Down:
      if (! stoneMoveDown()) {
        soundCtrl(SOUND_LOCK);
        stoneLock();
        state = e_ClearRowInit;
      } else {
        proceedDelay = delayFactor(level);
        state = e_DownDelay;
      }
      break;

// --- phase: clear rows --------------------------------------------------
    case e_ClearRowInit:
      clearCheckCnt = 0;
      state = e_ClearRowCheck;
      break;

    case e_ClearRowNext:
      if (clearCheckCnt >= CANVAS_HEIGHT) {
        state = e_NewStone;
      } else {
        clearCheckCnt += 1;
        state = e_ClearRowCheck;
      }
      break;

    case e_ClearRowCheck:
      if (canvasIsRowFilled(clearCheckCnt)) {
        score += level;
        if (score > eepromReadHighScore()) {
          newHighScoreAchieved = true;
          eepromSetHighScore(score);
          eepromCommit();
        }
        state = e_ClearRowFlash;
      } else {
        state = e_ClearRowNext;
      }
      break;

    case e_ClearRowFlash:
      canvasFillRow(clearCheckCnt, eepromReadFlashColor());
      state = e_ClearRowFlashDelay;
      break;

    case e_ClearRowFlashDelay:
      state = e_ClearRowWipe;
      break;

    case e_ClearRowWipe:
      canvasWipeRow(clearCheckCnt);
      filledLines += 1;

      if ((filledLines > 0) && ((filledLines % 10) == 0)) {
        if (level < MAX_LEVEL) {
          level += 1;
        }
        soundCtrl(SOUND_FANFARE); 
      } else {
        soundCtrl(SOUND_PLING);
      }
      state = e_ClearRowNext;
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

#ifndef STATE_DEBUGGING  
  if (isGameActive()) {
    displaySetValue(score);
  } else {
    displaySetValue(eepromReadHighScore());
  }
#endif 
}

void gameInit() {
  schAdd(gameExec, NULL, 0, GAME_CYCLE_TIME);
}

