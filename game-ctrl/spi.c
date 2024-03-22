#include <msp430g2553.h>
#include "spi.h"

void spiInit() {
  // SPI in master mode, most significant bit first
  UCB0CTL0 = UCMST | UCMSB;
  // SPI timing config
  UCB0CTL1 = UCSSEL_3;
  // Faster than 8 ends up in strange communication errors
  // between the both MCUs.
  // With 8 the transfer of a complete 110 pixel canvas takes
  // about 720us.
  // 8 was still too fast and caused problems.
  UCB0BR0 = 16; 
  UCB0BR1 = 0;

  // BIT5: UCB0CLK
  // BIT6: UCB0SOMI
  // BIT7: UCB0SIMO
  P1SEL |= BIT5 | BIT6 | BIT7;
  P1SEL2 |= BIT5 | BIT6 | BIT7;
  P1DIR |= BIT5 | BIT7;

  // Device Select Lines: 0: Canvas, 1: Display, 2: Sound
  P1DIR |= BIT0 | BIT1 | BIT2;
  // Disable all of them
  P1OUT |= BIT0 | BIT1 | BIT2;

  // enable SPI module
  UCB0CTL1 &= ~UCSWRST;
}

void spiSendBegin(t_SpiDeviceSelector d) {
  uint16_t bit = ((uint16_t[]){ BIT0, BIT1, BIT2 })[d];
  P1OUT &= ~bit;
}

void spiSendEnd(t_SpiDeviceSelector d) {
  while (UCB0STAT & UCBUSY);
  uint16_t bit = ((uint16_t[]){ BIT0, BIT1, BIT2 })[d];
  P1OUT |= bit;
}

void spiSendOctet(uint8_t v) {
  // wait for TX buffer empty
  while (!(UC0IFG & UCB0TXIFG));
  // load octet into TX buffer
  UCB0TXBUF = v;
}

