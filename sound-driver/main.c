#include <msp430g2553.h>
#include <stdint.h>
#include <stdlib.h>

#include "spi.h"
#include "psg.h"
#include "scheduler.h"
#include "sequencer.h"
#include "melody_tetris.h"
#include "melody_tusch1.h"
#include "mute.h"
#include "effects.h"

int main() {
  WDTCTL = WDTPW | WDTHOLD;

  __disable_interrupt();

  // highest possible system clock
  DCOCTL = DCO0 | DCO1 | DCO2;
  BCSCTL1 = XT2OFF | RSEL0 | RSEL1 | RSEL2 | RSEL3;
  BCSCTL2 = 0;
  BCSCTL3 = 0;


  schInit();

  spiInit();
  psgInit();
  muteInit();
  sequencerInit();
  effectsInit();

  __enable_interrupt();

  while (1) {
    schExec();
  }
}
