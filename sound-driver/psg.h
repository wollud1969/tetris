#ifndef _PSG_H_
#define _PSG_H_

#include <stdint.h>

typedef enum {
  e_O_1 = 0,
  e_O_2,
  e_O_3,
  e_O_4,
  e_O_5,
  e_O_6,
  e_O_7,
  e_O_8,
  e_O_Null
} t_octave;

typedef enum {
  e_C = 0,
  e_Cis,
  e_D,
  e_Dis,
  e_E,
  e_F,
  e_Fis,
  e_G,
  e_Gis,
  e_A,
  e_Ais,
  e_H,
  e_Pause,
  e_Null
} t_note;
    
#define e_Es e_Dis
#define e_As e_Gis
#define e_B e_Ais

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


void psgInit();

void psgPlayTone(uint8_t chip, uint8_t channel, uint8_t volume, t_octave octave, t_note note);
void psgAmplitude(uint8_t chip, uint8_t channel, uint8_t volume);
uint8_t psgReadShadow(uint8_t chip, uint8_t address);
void psgWrite(uint8_t chip, uint8_t address, uint8_t data);

#endif // _PSG_H_
