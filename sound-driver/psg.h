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


void psgInit();

void psgPlayTone(uint8_t chip, uint8_t channel, uint8_t volume, t_octave octave, t_note note);
void psgAmplitude(uint8_t chip, uint8_t channel, uint8_t volume);


#endif // _PSG_H_
