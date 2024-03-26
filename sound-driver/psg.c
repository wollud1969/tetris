#include <msp430g2553.h>
#include <stdint.h>
#include <stdlib.h>

#include "psg.h"
#include "scheduler.h"
#include "notes.h"


#define ADDR_DATA_REG P2OUT
#define BUS_CTRL_REG P1OUT
#define BC1 BIT3
#define BDIR BIT1

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

  // put bus into inactive state
  BUS_OP_NACT();

  // put address on bus
  ADDR_DATA_REG = address;

  // address latch mode
  BUS_OP_INTAK();

  // latch address
  BUS_OP_NACT();

  // put data on bus
  ADDR_DATA_REG = data;
  
  // set write to psg
  BUS_OP_DWS();

  // set inactive again
  BUS_OP_NACT();
}

static void writeFrequency(uint8_t channel, uint16_t frequencyCode) {
  writePSG(R0 + (channel * 2), (frequencyCode & 0x00ff));
  writePSG(R1 + (channel * 2), ((frequencyCode >> 8) & 0x000f));
}

void psgPlayTone(uint8_t channel, t_octave octave, t_note note) {
  writeFrequency(channel, frequencyCodes[octave][note]);
}

void playSomething(void *handle) {
  static uint8_t state = 0;

  switch (state) {
    case 0:
      writePSG(R7, 0b11111110);
      writePSG(R10, 03);
      state = 1;
      // no break;
    
    case 1:
      psgPlayTone(0, e_O_5, e_C);
      state = 2;
      break;

    case 2:
      psgPlayTone(0, e_O_5, e_E);
      state = 1;
      break;
  }
}

void psgInit() {
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
  // BIT3: BC1
  // BIT1: BDIR
  P1DIR |= BIT1 | BIT3;

  // put bus into inactive state
  BUS_CTRL_REG &= ~(BDIR | BC1);
  
  // release sound chip from reset state
  P1OUT |= BIT2;
  delay();
  delay();
  delay();

  schAdd(playSomething, NULL, 0, 500);
}




  /*
  // single tone
  writePSG(R0, 0376);
  writePSG(R1, 0);
  writePSG(R7, 076);
  writePSG(R10, 03);
  */

  /*
  // gun shot
  writePSG(R6, 017);
  writePSG(R7, 007);
  writePSG(R10, 020);
  writePSG(R11, 020);
  writePSG(R12, 020);
  writePSG(R14, 020);
  writePSG(R15, 0);
  */

  /*
  // explosion
  writePSG(R6, 0);
  writePSG(R7, 007);
  writePSG(R10, 020);
  writePSG(R11, 020);
  writePSG(R12, 020);
  writePSG(R14, 070);
  writePSG(R15, 0);
  */

  /*
  // Akkord
  writeFrequency(0, C5);
  writeFrequency(1, E5);
  writeFrequency(2, G5);
  writePSG(R7, 0b11111000);
  writePSG(R10, 03);
  writePSG(R11, 03);
  writePSG(R12, 03);
  */



