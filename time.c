#include <msp430g2553.h>

#include "time.h"
#include "PontCoopScheduler.h"


void __attribute__ ((interrupt (TIMER0_A0_VECTOR))) ta0_isr() {
  schUpdate();
}

void timeInit() {
  TACCR0 = 32;
  TACCTL0 = CCIE;
  TACTL = MC_1 | ID_0 | TASSEL_1 | TACLR;
}

