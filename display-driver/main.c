#include <msp430g2553.h>
#include <stdint.h>
#include <stdlib.h>


const uint8_t patterns[] = {
  0b00111111, // 0
  0b00000110, // 1
  0b01011011, // 2
  0b01001111, // 3
  0b01100110, // 4
  0b01101101, // 5
  0b01111101, // 6
  0b00100111, // 7
  0b01111111, // 8
  0b01101111, // 9
};



volatile union {
  uint16_t value;
  uint8_t receiveBuffer[2];
} value;


static void delay() {
  asm volatile (
      "push r12\n"
      "mov.w #1000, r12\n"
      "loop:\n"
      "dec.w r12\n"
      "jnz loop\n"
      "pop r12\n"
  );
}


void __attribute__ ((interrupt (USCIAB0RX_VECTOR))) receive() {
  static uint8_t octetNumber = 0;
  if (UC0IFG & UCB0RXIFG) {
    value.receiveBuffer[octetNumber] = UCB0RXBUF;
    octetNumber++;
    if (octetNumber > 1) {
      octetNumber = 0;
    }
  }
}

// mask 0x0f: digit value
// mask 0x10: set dp
// mask 0x20: digit off
static void setDigit(uint16_t bit, uint8_t value) {
  P1OUT |= (BIT0 | BIT1 | BIT2 | BIT3);
  P2OUT = ((value & 0x20) ? 0 : patterns[value & 0x0f]) | ((value & 0x10) ? 0x80 : 0x00);
  P1OUT &= ~bit;
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

  // digit driver
  P1DIR |= BIT0 | BIT1 | BIT2 | BIT3;
  P1SEL &= ~(BIT0 | BIT1 | BIT2 | BIT3);
  P1SEL2 &= ~(BIT0 | BIT1 | BIT2 | BIT3);

  // segment driver
  P2DIR = 0xff;
  P2SEL = 0x00;
  P2SEL2 = 0x00;

  // all digits off
  P1OUT |= (BIT0 | BIT1 | BIT2 | BIT3);

  // all segments off
  P2OUT &= ~(BIT0 | BIT1 | BIT2 | BIT3 | BIT4 | BIT5 | BIT6 | BIT7);

  // reset value to 0
  value.value = 0;

  __enable_interrupt();

  while (1) {
    __disable_interrupt();
    uint16_t shadowValue = value.value;
    __enable_interrupt();

    uint8_t digit0 = shadowValue % 10;
    uint8_t digit1 = (shadowValue / 10) % 10;
    uint8_t digit2 = (shadowValue / 100) % 10;
    uint8_t digit3 = (shadowValue / 1000) % 10;

    digit1 += (!((digit3 & 0x0f) | (digit2 & 0x0f) | (digit1 & 0x0f))) ? 0x20 : 0x00;
    digit2 += (!((digit3 & 0x0f) | (digit2 & 0x0f))) ? 0x20 : 0x00;
    digit3 += (!(digit3 & 0x0f)) ? 0x20 : 0x00;

    setDigit(BIT0, digit0);
    delay();

    setDigit(BIT1, digit1);
    delay();

    setDigit(BIT2, digit2);
    delay();

    setDigit(BIT3, digit3);
    delay();
  }
}
