#include "led.h"
#include <msp430g2553.h>
#include "PontCoopScheduler.h"
#include <stdlib.h>


void ledGreenOn() {
  P1OUT |= BIT0;
}

void ledGreenOff() {
  P1OUT &= ~BIT0;
}

void ledBlueOn() {
  P1OUT |= BIT1;
}

void ledBlueOff() {
  P1OUT &= ~BIT1;
}

void ledExec() {
  static int i = 0;

  if (i == 0) {
    ledGreenOff();
    ledBlueOn();
    i = 1;
  } else {
    ledGreenOn();
    ledBlueOff();
    i = 0;
  }
}

void ledInit() {
    // BIT0: green
    // BIT1: blue
    P1DIR |= BIT0|BIT1;
    P1OUT |= BIT0|BIT1;

    schAdd(ledExec, NULL, 0, 50);
}


