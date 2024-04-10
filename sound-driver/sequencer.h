#ifndef _SEQUENCER_H_
#define _SEQUENCER_H_


#include <stdint.h>
#include <stdbool.h>
#include "psg.h"

typedef enum {
  e_L_1 = 0,
  e_L_1_2 = 1,
  e_L_1_4 = 2,
  e_L_1_8 = 3,
  e_L_1_16 = 4,
  e_L_1_32 = 5,
  e_L_LengthEnd = 6,
  e_L_HoldMark = 252,
  e_L_StopMark = 253,
  e_L_EndMark = 254,
  e_L_SyncMark = 255,
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
  e_Sync,
  e_HoldTone, 
  e_StaccatoBreak,
  e_HoldStaccatoBreak,
  e_SeparateTone,
  e_Hold,
  e_Terminate
} t_sequencerState;

typedef struct {
  uint16_t idx;
  uint8_t chip;
  uint16_t lengthCnt;
  t_sequencerState state;
  uint8_t amplitude;
  const t_tone *tones;
} t_melody;

#define SEQUENCER_PERIOD 4 // ms
#define NUM_OF_CHANNELS 3
typedef struct {
  uint8_t taskId;
  bool firstRun;
  uint8_t numOfMelodies;
  uint8_t pace; // quarter notes per minute
  uint8_t sync;
  t_melody melodies[NUM_OF_CHANNELS];
} t_melodies;

void sequencerInit();
uint16_t sequencerPlayMelodies(t_melodies *melodies);


#endif // _SEQUENCER_H_
