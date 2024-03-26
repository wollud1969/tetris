#include "psg.h"
#include "sequencer.h"


/*
const t_note notes[] = {
  { .octave = e_O_2, .note = e_G,   .length = },
  { .octave = e_O_2, .note = e_D,   .length = },
  { .octave = e_O_2, .note = e_Dis, .length = },

  { .octave = e_O_2, .note = e_F,   .length = },
  { .octave = e_O_2, .note = e_Dis, .length = },
  { .octave = e_O_2, .note = e_D,   .length = },

  { .octave = e_O_2, .note = e_C,   .length = },
  { .octave = e_O_2, .note = e_C,   .length = },
  { .octave = e_O_2, .note = e_Dis, .length = },

  { .octave = e_O_2, .note = e_G,   .length = },
  { .octave = e_O_2, .note = e_F,   .length = },
  { .octave = e_O_2, .note = e_Dis, .length = },

  { .octave = e_O_2, .note = e_D,   .length = },
  { .octave = e_O_2, .note = e_D,   .length = },
  { .octave = e_O_2, .note = e_Dis, .length = },

  { .octave = e_O_2, .note = e_F,   .length = },
  { .octave = e_O_2, .note = e_G,   .length = },

  { .octave = e_O_2, .note = e_Dis, .length = },
  { .octave = e_O_2, .note = e_C,   .length = },

  { .octave = e_O_2, .note = e_C,   .length = },
};
*/

const t_tone ladder[16] = {
  { .octave = e_O_2, .note = e_C,   .length = e_L_1_4 },
  { .octave = e_O_2, .note = e_D,   .length = e_L_1_4 },
  { .octave = e_O_2, .note = e_E,   .length = e_L_1_4 },
  { .octave = e_O_2, .note = e_F,   .length = e_L_1_4 },
  { .octave = e_O_2, .note = e_G,   .length = e_L_1_4 },
  { .octave = e_O_2, .note = e_A,   .length = e_L_1_4 },
  { .octave = e_O_2, .note = e_H,   .length = e_L_1_4 },
  { .octave = e_O_3, .note = e_C,   .length = e_L_1_4 },
  { .octave = e_O_2, .note = e_H,   .length = e_L_1_4 },
  { .octave = e_O_2, .note = e_A,   .length = e_L_1_4 },
  { .octave = e_O_2, .note = e_G,   .length = e_L_1_4 },
  { .octave = e_O_2, .note = e_F,   .length = e_L_1_4 },
  { .octave = e_O_2, .note = e_E,   .length = e_L_1_4 },
  { .octave = e_O_2, .note = e_D,   .length = e_L_1_4 },
  { .octave = e_O_2, .note = e_H,   .length = e_L_EndMark },
};

t_melody melodyLadder = {
  .idx = 0,
  .lengthCnt = 0,
  .tones = ladder
};


void melodyInit() {
  psgWrite(07, 0b11111110);
  psgWrite(010, 03);
  sequencerPlayMelody(&melodyLadder);
}


