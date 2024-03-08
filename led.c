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

void ledExec(void *args) {
  static uint16_t i = 0;

  if (i == 0) {
    ledGreenOff();
    i = 1;
  } else {
    ledGreenOn();
    i = 0;
  }
}

void ledInit() {
    // BIT0: green
    // BIT1: blue
    P1DIR |= BIT0|BIT1;

    ledGreenOff();
    ledBlueOff();


    schAdd(ledExec, NULL, 0, 500);
}


