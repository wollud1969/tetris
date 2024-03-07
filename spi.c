#include "spi.h"
#include <msp430g2553.h>
#include "PontCoopScheduler.h"
#include <stdlib.h>
#include <stdint.h>



static void spiSendOctet(uint8_t v) {
  while (!(UC0IFG & UCB0TXIFG));
  UCB0TXBUF = v;
}

void spiExec() {
  // enable spi
  UCB0CTL1 &= ~UCSWRST;

  spiSendOctet(0x00);
  spiSendOctet(0x0d);

  // disable spi
  UCB0CTL1 |= UCSWRST;

  // reschedule
  schAdd(spiExec, NULL, 1000, 0);
}

void spiInit() {
  UCB0CTL0 = UCMST | UCSYNC;
  UCB0CTL1 = UCSSEL_3;
  UCB0BR0 = 8;
  UCB0BR1 = 0;

  // UCB0CLK, UCB0SOMI, UCB0SIMO
  P1SEL |= BIT5 | BIT6 | BIT7;
  P1SEL2 |= BIT5 | BIT6 | BIT7;
  P1OUT |= BIT5 | BIT7;

  // P1.3 is signal line
  P1DIR &= ~BIT3;

  schAdd(spiExec, NULL, 1000, 0);
}


