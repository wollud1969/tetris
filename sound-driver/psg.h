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
    

void psgInit();
void psgPlayTone(uint8_t channel, t_octave octave, t_note note);
void psgWriteFrequency(uint8_t channel, uint16_t frequencyCode);
void psgWrite(uint8_t address, uint8_t data);
uint8_t psgReadShadow(uint8_t address);

#endif // _PSG_H_
