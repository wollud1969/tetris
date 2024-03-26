#include <stdbool.h>
#include "psg.h"
#include "sequencer.h"


const t_tone notes[] = {
  { .octave = e_O_3,    .note = e_G,     .length = e_L_1_4,     .legato = false },
  { .octave = e_O_3,    .note = e_D,     .length = e_L_1_8,     .legato = false },
  { .octave = e_O_3,    .note = e_Dis,   .length = e_L_1_8,     .legato = false },

  { .octave = e_O_3,    .note = e_F,     .length = e_L_1_4,     .legato = false },
  { .octave = e_O_3,    .note = e_Dis,   .length = e_L_1_8,     .legato = false },
  { .octave = e_O_3,    .note = e_D,     .length = e_L_1_8,     .legato = false },

  { .octave = e_O_3,    .note = e_C,     .length = e_L_1_4,     .legato = false },
  { .octave = e_O_3,    .note = e_C,     .length = e_L_1_8,     .legato = false },
  { .octave = e_O_3,    .note = e_Dis,   .length = e_L_1_8,     .legato = false },

  { .octave = e_O_3,    .note = e_G,     .length = e_L_1_4,     .legato = false },
  { .octave = e_O_3,    .note = e_F,     .length = e_L_1_8,     .legato = false },
  { .octave = e_O_3,    .note = e_Dis,   .length = e_L_1_8,     .legato = false },

  { .octave = e_O_3,    .note = e_D,     .length = e_L_1_4,     .legato = true  },
  { .octave = e_O_3,    .note = e_D,     .length = e_L_1_8,     .legato = false },
  { .octave = e_O_3,    .note = e_Dis,   .length = e_L_1_8,     .legato = false },

  { .octave = e_O_3,    .note = e_F,     .length = e_L_1_4,     .legato = false },
  { .octave = e_O_3,    .note = e_G,     .length = e_L_1_4,     .legato = false },

  { .octave = e_O_3,    .note = e_Dis,   .length = e_L_1_8,     .legato = true  },
  { .octave = e_O_3,    .note = e_Dis,   .length = e_L_1_16,    .legato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_16,    .legato = false },
  { .octave = e_O_3,    .note = e_C,     .length = e_L_1_8,     .legato = true  },
  { .octave = e_O_3,    .note = e_C,     .length = e_L_1_16,    .legato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_16,    .legato = false },

  { .octave = e_O_3,    .note = e_C,     .length = e_L_1_4,     .legato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_4,     .legato = false },


  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false },
  { .octave = e_O_3,    .note = e_F,     .length = e_L_1_8,     .legato = true  },
  { .octave = e_O_3,    .note = e_F,     .length = e_L_1_8,     .legato = false },
  { .octave = e_O_3,    .note = e_Gis,   .length = e_L_1_8,     .legato = false },

  { .octave = e_O_4,    .note = e_C,     .length = e_L_1_4,     .legato = false },
  { .octave = e_O_3,    .note = e_Ais,   .length = e_L_1_8,     .legato = false },
  { .octave = e_O_3,    .note = e_Gis,   .length = e_L_1_8,     .legato = false },

  { .octave = e_O_3,    .note = e_G,     .length = e_L_1_4,     .legato = true  },
  { .octave = e_O_3,    .note = e_G,     .length = e_L_1_8,     .legato = false },
  { .octave = e_O_3,    .note = e_Dis,   .length = e_L_1_8,     .legato = false },

  { .octave = e_O_3,    .note = e_G,     .length = e_L_1_4,     .legato = false },
  { .octave = e_O_3,    .note = e_F,     .length = e_L_1_8,     .legato = false },
  { .octave = e_O_3,    .note = e_Dis,   .length = e_L_1_8,     .legato = false },

  { .octave = e_O_3,    .note = e_D,     .length = e_L_1_4,     .legato = false },
  { .octave = e_O_3,    .note = e_D,     .length = e_L_1_8,     .legato = false },
  { .octave = e_O_3,    .note = e_Dis,   .length = e_L_1_8,     .legato = false },

  { .octave = e_O_3,    .note = e_F,     .length = e_L_1_4,     .legato = false },
  { .octave = e_O_3,    .note = e_G,     .length = e_L_1_4,     .legato = false },

  { .octave = e_O_3,    .note = e_Dis,   .length = e_L_1_8,     .legato = true  },
  { .octave = e_O_3,    .note = e_Dis,   .length = e_L_1_16,    .legato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_16,    .legato = false },
  { .octave = e_O_3,    .note = e_C,     .length = e_L_1_8,     .legato = true  },
  { .octave = e_O_3,    .note = e_C,     .length = e_L_1_16,    .legato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_16,    .legato = false },

  { .octave = e_O_3,    .note = e_C,     .length = e_L_1_4,     .legato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_4,     .legato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_EndMark, .legato = false },
};

/*
const t_tone ladder[16] = {
  { .octave = e_O_3, .note = e_C,   .length = e_L_1_4 },
  { .octave = e_O_3, .note = e_D,   .length = e_L_1_4 },
  { .octave = e_O_3, .note = e_E,   .length = e_L_1_4 },
  { .octave = e_O_3, .note = e_F,   .length = e_L_1_4 },
  { .octave = e_O_3, .note = e_G,   .length = e_L_1_4 },
  { .octave = e_O_3, .note = e_A,   .length = e_L_1_4 },
  { .octave = e_O_3, .note = e_H,   .length = e_L_1_4 },
  { .octave = e_O_4, .note = e_C,   .length = e_L_1_4 },
  { .octave = e_O_3, .note = e_H,   .length = e_L_1_4 },
  { .octave = e_O_3, .note = e_A,   .length = e_L_1_4 },
  { .octave = e_O_3, .note = e_G,   .length = e_L_1_4 },
  { .octave = e_O_3, .note = e_F,   .length = e_L_1_4 },
  { .octave = e_O_3, .note = e_E,   .length = e_L_1_4 },
  { .octave = e_O_3, .note = e_D,   .length = e_L_1_4 },
  { .octave = e_O_3, .note = e_H,   .length = e_L_EndMark },
};
*/

t_melody melody= {
  .idx = 0,
  .lengthCnt = 0,
  .tones = notes
};


void melodyInit() {
  psgWrite(07, 0b11111110);
  psgWrite(010, 03);
  sequencerPlayMelody(&melody);
}


