#ifndef _PSG_H_
#define _PSG_H_


typedef enum {
  e_O_1 = 0,
  e_O_2,
  e_O_3,
  e_O_4,
  e_O_5,
  e_O_6,
  e_O_7,
  e_O_8
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
  e_H
} t_note;

typedef enum {
  e_L_1 = 80,
  e_L_1_2 = 40,
  e_L_1_4 = 20,
  e_L_1_8 = 10,
  e_L_1_16 = 5
} t_noteLength;
    

void psgInit();
void psgPlayTone(uint8_t channel, t_octave octave, t_note note);


#endif // _PSG_H_
