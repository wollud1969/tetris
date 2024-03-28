#include <msp430g2553.h>
#include <stdint.h>
#include <stdlib.h>

#include "psg.h"
#include "scheduler.h"



const uint16_t frequencyCodes[8][12] = {
  //    C,   Cis,     D,   Dis,     E,     F,   Fis,     G,   Gis,     A,   Ais,     H
  { 06535, 06234, 05747, 05474, 05233, 05002, 04563, 04353, 04153, 03762, 03600, 03424 },  // Octave 1
  { 03256, 03116, 02764, 02636, 02515, 02401, 02271, 02165, 02065, 01771, 01700, 01612 },  // Octave 2
  { 01527, 01447, 01372, 01317, 01247, 01201, 01135, 01073, 01033, 00774, 00740, 00705 },  // Octave 3
  { 00654, 00624, 00575, 00550, 00523, 00500, 00456, 00435, 00415, 00376, 00360, 00342 },  // Octave 4
  { 00326, 00312, 00276, 00264, 00252, 00240, 00227, 00217, 00207, 00177, 00170, 00161 },  // Octave 5
  { 00153, 00145, 00137, 00132, 00125, 00120, 00114, 00107, 00103, 00100, 00074, 00071 },  // Octave 6
  { 00065, 00062, 00060, 00055, 00052, 00050, 00046, 00044, 00042, 00040, 00036, 00034 },  // Octave 7
  { 00033, 00031, 00030, 00026, 00025, 00024, 00023, 00022, 00021, 00020, 00017, 00016 }   // Octave 8
};


#define ADDR_DATA_REG P2OUT
#define BUS_CTRL_REG P1OUT
#define BC1 BIT3
#define BDIR BIT1

#define R0 0
#define CHANNEL_A_TONE_PERIOD_FINE_REG R0
#define R1 1
#define CHANNEL_A_TONE_PERIOD_COARSE_REG R1
#define R2 2
#define CHANNEL_B_TONE_PERIOD_FINE_REG R2
#define R3 3
#define CHANNEL_B_TONE_PERIOD_COARSE_REG R3
#define R4 4
#define CHANNEL_C_TONE_PERIOD_FINE_REG R4
#define R5 5
#define CHANNEL_C_TONE_PERIOD_COARSE_REG R5
#define R6 6
#define NOISE_PERIOD_REG R6
#define R7 7
#define _ENABLE_REG R7
#define R10 010
#define CHANNEL_A_AMPLITUDE_REG R10
#define R11 011
#define CHANNEL_B_AMPLITUDE_REG R11
#define R12 012
#define CHANNEL_C_AMPLITUDE_REG R12
#define R13 013
#define ENVELOPE_PERIOD_FINE_REG R13
#define R14 014
#define ENVELOPE_PERIOD_COARSE_REG R13
#define R15 015
#define ENVELOPE_SHAPE_REG R15

uint8_t psgShadowRegisters[14];

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

uint8_t psgReadShadow(uint8_t address) {
  return psgShadowRegisters[address];
}

void psgWrite(uint8_t address, uint8_t data) {
  psgShadowRegisters[address] = data;

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

void psgWriteFrequency(uint8_t channel, uint16_t frequencyCode) {
  psgWrite(CHANNEL_A_TONE_PERIOD_FINE_REG + (channel * 2), (frequencyCode & 0x00ff));
  psgWrite(CHANNEL_A_TONE_PERIOD_COARSE_REG + (channel * 2), ((frequencyCode >> 8) & 0x000f));
}

void psgPlayTone(uint8_t channel, t_octave octave, t_note note) {
  if (note == e_Pause) {
    psgWrite(_ENABLE_REG, psgReadShadow(_ENABLE_REG) | (1 << channel));
  } else {
    psgWrite(_ENABLE_REG, psgReadShadow(_ENABLE_REG) & ~(1 << channel));
    psgWriteFrequency(channel, frequencyCodes[octave][note]);
  }
}

void psgAmplitude(uint8_t channel, uint8_t volume) {
  psgWrite(CHANNEL_A_AMPLITUDE_REG + channel, volume);
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

  // disable everything
  psgWrite(_ENABLE_REG, 0xff);
}

