#include <msp430g2553.h>
#include <stdint.h>
#include <stdlib.h>



void __attribute__ ((interrupt (USCIAB0RX_VECTOR))) receive() {
  if (UC0IFG & UCB0RXIFG) {
    // receive an octet
  }
}


int main() {
  WDTCTL = WDTPW | WDTHOLD;

  __disable_interrupt();

  // highest possible system clock
  DCOCTL = DCO0 | DCO1 | DCO2;
  BCSCTL1 = XT2OFF | RSEL0 | RSEL1 | RSEL2 | RSEL3;
  BCSCTL2 = 0;
  BCSCTL3 = 0;

  // SPI slave
  // BIT4: UCB0STE
  // BIT5: UCB0CLK
  // BIT6: UCB0SOMI
  // BIT7: UCB0SIMO
  P1SEL |= BIT4 | BIT5 | BIT6 | BIT7;
  P1SEL2 |= BIT4 | BIT5 | BIT6 | BIT7;
  // most significant bit first, enable STE
  UCB0CTL0 = UCSYNC | UCMSB | UCMODE_2;
  UCB0CTL1 = 0x00;
  // enable RX interrupt
  UC0IE |= UCB0RXIE;


  __enable_interrupt();

  while (1) {
  }
}
