#include <stddef.h>
#include <msp430g2553.h>
#include <stdint.h>
#include "scheduler.h"
#include "spi.h"
#include "soundCodes.h"
#include "config.h"


volatile uint8_t cmd;

void spiInit() {
  // SPI slave
  // BIT4: UCB0STE
  // BIT5: UCB0CLK
  // BIT6: UCB0SOMI
  // BIT7: UCB0SIMO
  P1SEL |= BIT4 | BIT5 | BIT7;
  P1SEL2 |= BIT4 | BIT5 | BIT7;

  // most significant bit first, enable STE
  UCB0CTL0 = UCCKPH | UCSYNC | UCMSB | UCMODE_2;
  UCB0CTL1 = 0x00;

  // enable RX interrupt
  UC0IE |= UCB0RXIE;

  cmd = SOUND_IDLE;
  schAdd(spiCmdHandler, NULL, 0, 5);
}

void spiCommandDispatcher() {
  cmd &= ~SOUND_COMMAND;

  if (cmd & SOUND_SUBCMD_AMPLITUDE) {
    cmd &= ~SOUND_SUBCMD_AMPLITUDE;
    configSetAmplitude(cmd);
  }
}
