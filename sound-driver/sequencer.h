#ifndef _SEQUENCER_H_
#define _SEQUENCER_H_


#include <stdint.h>
#include <stdbool.h>
#include "psg.h"

typedef enum {
  e_L_EndMark = 0,
  e_L_1 = 320,
  e_L_1_2 = 160,
  e_L_1_4 = 80,
  e_L_1_8 = 40,
  e_L_1_16 = 20,
  e_L_1_32 = 10,
} t_noteLength;

typedef struct {
  t_octave octave;
  t_note note;
  t_noteLength length;
  bool legato; 
  bool staccato;
} t_tone;

typedef enum { 
  e_Init,
  e_PlayTone, 
  e_HoldTone, 
  e_StaccatoBreak,
  e_HoldStaccatoBreak,
  e_SeparateTone 
} t_sequencerState;

typedef struct {
  uint16_t idx;
  uint8_t lengthCnt;
  t_sequencerState state;
  uint8_t pace;
  uint8_t amplitude;
  uint8_t channel;
  const t_tone *tones;
} t_melody;

void sequencerInit();
uint16_t sequencerPlayMelody(t_melody *melody);


#endif // _SEQUENCER_H_
