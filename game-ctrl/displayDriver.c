#include "displayDriver.h"
#include "led.h"
#include "canvas.h"
#include <msp430g2553.h>
#include <stdlib.h>
#include <stdint.h>



inline static void spiSendOctet(uint8_t v) {
  // wait for TX buffer empty
  while (!(UC0IFG & UCB0TXIFG));
  // load octet into TX buffer
  UCB0TXBUF = v;
}

void displayDriverTransferCanvas() {
  // wait for signal waiting for data
  while ((P1IN & BIT3) == 0);

  for (uint8_t i = 0; i < canvas.size; i++) {
    if ((*((canvas.canvas)+i) & 0x80) != 0) {
      *((canvas.canvas)+i) &= ~0x80;
      spiSendOctet(i);
      spiSendOctet(*((canvas.canvas)+i));
    }
  }
  spiSendOctet(0xfe);
}

void displayDriverInit() {
  // SPI in master mode
  UCB0CTL0 = UCMST;
  // SPI timing config
  UCB0CTL1 = UCSSEL_3;
  // Faster than 8 ends up in strange communication errors
  // between the both MCUs.
  // With 8 the transfer of a complete 110 pixel canvas takes
  // about 720us.
  UCB0BR0 = 8; 
  UCB0BR1 = 0;

  // BIT5: UCB0CLK
  // BIT6: UCB0SOMI
  // BIT7: UCB0SIMO
  P1SEL |= BIT5 | BIT6 | BIT7;
  P1SEL2 |= BIT5 | BIT6 | BIT7;
  P1DIR |= BIT5 | BIT7;

  // P1.3 is signal line
  P1DIR &= ~BIT3;

  // enable SPI module
  UCB0CTL1 &= ~UCSWRST;
}


