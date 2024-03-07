#include <msp430g2553.h>
#include <stdint.h>

#include "time.h"
#include "PontCoopScheduler.h"


volatile uint32_t timestamp;

void __attribute__ ((interrupt (TIMER0_A0_VECTOR))) ta0_isr() {
  timestamp++;
  schUpdate();
}

void timeInit() {
  timestamp = 0;

  TACCR0 = 32;
  TACCTL0 = CCIE;
  TACTL = MC_1 | ID_0 | TASSEL_1 | TACLR;
}

uint32_t getMillis() {
  return timestamp;
}

void ms_active_delay(uint16_t delay) {
  uint32_t start = timestamp;
  while (start + delay > timestamp);
}
