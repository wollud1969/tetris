#include <msp430g2553.h>
#include <stdint.h>
#include <stdlib.h>

#include "psg.h"
#include "scheduler.h"
#include "notes.h"



const uint16_t frequencyCodes[8][12] = {
  { 06535, 06234, 05747, 05474, 05233, 05002, 04563, 04353, 04153, 03762, 03600, 03424 },
  { 03256, 03116, 02764, 02636, 02515, 02401, 02271, 02165, 02065, 01771, 01700, 01612 },
  { 01527, 01447, 01372, 01317, 01247, 01201, 01135, 01073, 01033, 00774, 00740, 00705 },
  { 00654, 00624, 00575, 00550, 00523, 00500, 00456, 00435, 00415, 00376, 00360, 00342 },
  { 00326, 00312, 00276, 00264, 00252, 00240, 00227, 00217, 00207, 00177, 00170, 00161 },
  { 00153, 00145, 00137, 00132, 00125, 00120, 00114, 00107, 00103, 00100, 00074, 00071 },
  { 00065, 00062, 00060, 00055, 00052, 00050, 00046, 00044, 00042, 00040, 00036, 00034 },
  { 00033, 00031, 00030, 00026, 00025, 00024, 00023, 00022, 00021, 00020, 00017, 00016 }
};


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



