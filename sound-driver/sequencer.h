#ifndef _SEQUENCER_H_
#define _SEQUENCER_H_


#include <stdint.h>
#include <stdbool.h>
#include "psg.h"

typedef enum {
  e_L_EndMark = 0,
  e_L_1 = 80,
  e_L_1_2 = 40,
  e_L_1_4 = 20,
  e_L_1_8 = 10,
  e_L_1_16 = 5
} t_noteLength;

typedef struct {
  t_octave octave;
  t_note note;
  t_noteLength length;
  bool legato; 
} t_tone;

typedef struct {
  uint16_t idx;
  uint8_t lengthCnt;
  uint8_t state;
  uint8_t channel;
  const t_tone *tones;
} t_melody;

void sequencerInit();
uint8_t sequencerPlayMelody(t_melody *melody);


#endif // _SEQUENCER_H_
