#include <stdint.h>
#include <stddef.h>
#include <msp430g2553.h>
#include "spi.h"
#include "../game-ctrl/sound.h"
#include "scheduler.h"

volatile t_SoundCmd cmd;

void __attribute__ ((interrupt (USCIAB0RX_VECTOR))) receive() {
  if (UC0IFG & UCB0RXIFG) {
    // receive an octet
    cmd = UCB0RXBUF;
  }
}

void spiCmdHandler(void *handle) {
  uint8_t cmdShadow;

  __disable_interrupt(); 
  cmdShadow = cmd;
  __enable_interrupt();

  /*
  e_SOUND_IDLE = 0,
  e_SOUND_MUTE = 1,
  e_SOUND_UNMUTE,
  e_SOUND_START_BACKGROUND,
  e_SOUND_STOP_BACKGROUND,
  e_SOUND_START_GAMEOVER,
  e_SOUND_STOP_GAMEOVER,
  e_SOUND_SPEED_UP,
  e_SOUND_FANFARE_BASE,
  e_SOUND_FANFARE_1,
  e_SOUND_FANFARE_2,
  e_SOUND_FANFARE_3,
  e_SOUND_FANFARE_4,
  e_SOUND_STONE_LOCKED,
  e_SOUND_STONE_MOVE_LEFT,
  e_SOUND_STONE_MOVE_RIGHT,
  e_SOUND_STONE_ROTATE_LEFT,
  e_SOUND_STONE_ROTATE_RIGHT,
  e_SOUND_STONE_MOVE_DOWN,
  */

  switch (cmdShadow) {
    case e_SOUND_MUTE:
      break;
    case e_SOUND_UNMUTE:
      break;
    case e_SOUND_START_BACKGROUND:
      break;
    case e_SOUND_STOP_BACKGROUND:
      break;
    case e_SOUND_START_GAMEOVER:
      break;
    case e_SOUND_STOP_GAMEOVER:
      break;
    case e_SOUND_SPEED_UP:
      break;
    case e_SOUND_FANFARE_1:
      break;
    case e_SOUND_FANFARE_2:
      break;
    case e_SOUND_FANFARE_3:
      break;
    case e_SOUND_FANFARE_4:
      break;
    case e_SOUND_STONE_LOCKED:
      break;
    case e_SOUND_STONE_MOVE_DOWN:
      break;
    case e_SOUND_STONE_MOVE_LEFT:
      break;
    case e_SOUND_STONE_MOVE_RIGHT:
      break;
    case e_SOUND_STONE_ROTATE_LEFT:
      break;
    case e_SOUND_STONE_ROTATE_RIGHT:
      break;
  }
}

void spiInit() {
  // SPI slave
  // BIT4: UCB0STE
  // BIT5: UCB0CLK
  // BIT6: UCB0SOMI
  // BIT7: UCB0SIMO
  P1SEL |= BIT4 | BIT5 | BIT7;
  P1SEL2 |= BIT4 | BIT5 | BIT7;

  // most significant bit first, enable STE
  UCB0CTL0 = UCSYNC | UCMSB | UCMODE_2;
  UCB0CTL1 = 0x00;

  // enable RX interrupt
  UC0IE |= UCB0RXIE;

  schAdd(spiCmdHandler, NULL, 0, 10);
}


