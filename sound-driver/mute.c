#include <msp430g2553.h>
#include "mute.h"



void muteInit() {
  // BIT6: MuteCtrl
  P1DIR |= BIT6;

  // initially, mute
  P1OUT |= BIT6;
}

void mute() {
  P1OUT |= BIT6;
}

void unMute() {
  P1OUT &= ~BIT6;
}


