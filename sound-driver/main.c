#include <msp430g2553.h>
#include <stdint.h>
#include <stdlib.h>


#define ADDR_DATA_REG P2OUT
#define BUS_CTRL_REG P1OUT
#define BC1 BIT0
#define BDIR BIT1
#define _CS BIT3

#define R0 0
#define R1 1
#define R2 2
#define R3 3
#define R4 4
#define R5 5
#define R6 6
#define R7 7
#define R10 010
#define R11 011
#define R12 012
#define R13 013
#define R14 014
#define R15 015

inline static void BUS_OP_ENABLE_CS() {
  BUS_CTRL_REG &= ~_CS;
}
inline static void BUS_OP_DISABLE_CS() {
  BUS_CTRL_REG |= _CS;
}
inline static void BUS_OP_NACT() {
  BUS_CTRL_REG &= ~(BDIR | BC1);
}
inline static void BUS_OP_INTAK() {
  BUS_CTRL_REG |= BDIR | BC1;
}
inline static void BUS_OP_DWS() {
  BUS_CTRL_REG |= BDIR;
  BUS_CTRL_REG &= ~BC1;
}

void __attribute__ ((interrupt (USCIAB0RX_VECTOR))) receive() {
  if (UC0IFG & UCB0RXIFG) {
    // receive an octet
  }
}


static void delay() {
asm volatile (
    "push r12\n"
    "mov.w #5, r12\n"
    "loop:\n"
    "dec.w r12\n"
    "jnz loop\n"
    "pop r12\n"
);
}

static void writePSG(uint8_t address, uint8_t data) {
  // according to "State Timing" (p. 15) of datasheet

  // select chip
  //BUS_OP_ENABLE_CS();

  // put bus into inactive state
  BUS_OP_NACT();

  delay();

  // put address on bus
  ADDR_DATA_REG = address;

  delay();

  // address latch mode
  BUS_OP_INTAK();

  delay();

  // latch address
  BUS_OP_NACT();

  delay();

  // put data on bus
  ADDR_DATA_REG = data;
  
  delay();

  // set write to psg
  BUS_OP_DWS();

  delay();

  // set inactive again
  BUS_OP_NACT();

  // deselect chip
  //BUS_OP_DISABLE_CS();
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

  // address/data bus
  P2DIR = 0xff;
  P2SEL = 0;
  P2SEL2 = 0;

  // sound chip reset
  // BIT2: /RST
  P1DIR |= BIT2;

  // put sound chip into reset state
  P1OUT &= ~BIT2;
  delay();
  delay();
  delay();
  
  // bus control lines
  // BIT0: BC1
  // BIT1: BDIR
  // BIT3: /CS
  P1DIR |= BIT0 | BIT1 | BIT3;

  // put bus into inactive state
  BUS_CTRL_REG &= ~(BDIR | BC1);
  BUS_CTRL_REG |= _CS;
  
  // release sound chip from reset state
  P1OUT |= BIT2;
  delay();
  delay();
  delay();
  

  __enable_interrupt();


  BUS_OP_ENABLE_CS();
  writePSG(R0, 0376);
  writePSG(R1, 0);
  writePSG(R7, 076);
  writePSG(R10, 03);
  BUS_OP_DISABLE_CS();


  while (1) {
  }
}
