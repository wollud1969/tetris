#include "stddef.h"
#include "stdint.h"

#include "game.h"
#include "scheduler.h"
#include "shapes.h"
#include "canvas.h"
#include "../rgb-driver/colors.h"
#include "display.h"
#include "sound.h"


#define GAME_CYCLE_TIME 100
#define GAMEOVER_DELAY 10


static uint8_t delayFactor(uint8_t level) {
  return 11 - level;
}

typedef enum {
  e_Phase_Game, e_Phase_GameOver 
} phase_t;

typedef enum { 
  e_Start, e_NewStone, e_Down, e_DownDelay, e_ClearRows,
  e_GameOver, e_GameOverFill, e_GameOverWipe, e_GameOverDelay 
} state_t;

void gameExec(void *handle) {
  static phase_t phase;
  static state_t state = e_Start;
  static uint8_t gameOverDelay;
  static uint8_t rowIndex;
  static uint8_t proceedDelay;
  static uint8_t level;
  static uint16_t score;

// --- engine begin -------------------------------------------------------
  switch (state) {
// --- phase: game --------------------------------------------------------
    case e_Start:
      canvasClear();
      soundCtrl(SOUND_START);
      level = 1;
      score = 0;
      displaySetValue(score);
      phase = e_Phase_Game;
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
        state = e_ClearRows;
      }
      break;

    case e_ClearRows:
      state = e_Down;
      break;
      
    case e_Down:
      if (! stoneMoveDown()) {
        soundCtrl(SOUND_LOCK);
        state = e_NewStone;
      } else {
        proceedDelay = delayFactor(level);
        state = e_DownDelay;
      }
      break;

// --- phase: game over ---------------------------------------------------
    case e_GameOver:
      soundCtrl(SOUND_GAMEOVER);
      rowIndex = CANVAS_HEIGHT;
      phase = e_Phase_GameOver;
      state = e_GameOverFill;
      break;

    case e_GameOverFill:
      rowIndex--;
      canvasFillRow(rowIndex, _red);
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
  if (phase == e_Phase_Game) {
    uint8_t wipeCnt = 0;
    for (uint8_t r = 0; r < CANVAS_HEIGHT; r++) {
      if (canvasIsRowFilled(r)) {
        score += level;
        displaySetValue(score);
        canvasWipeRow(r);
        canvasShow();
        wipeCnt += 1;
      }
    }
    if (wipeCnt != 0) {
      soundCtrl(SOUND_FANFARE); 
    }
  }
}

void gameInit() {
  schAdd(gameExec, NULL, 0, GAME_CYCLE_TIME);
}

