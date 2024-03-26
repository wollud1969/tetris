#include <stdbool.h>
#include "psg.h"
#include "sequencer.h"


const t_tone notes[] = {
  { .octave = e_O_3,    .note = e_G,     .length = e_L_1_4,     .legato = false },
  { .octave = e_O_3,    .note = e_D,     .length = e_L_1_8,     .legato = false },
  { .octave = e_O_3,    .note = e_Es,    .length = e_L_1_8,     .legato = false },

  { .octave = e_O_3,    .note = e_F,     .length = e_L_1_4,     .legato = false },
  { .octave = e_O_3,    .note = e_Es,    .length = e_L_1_8,     .legato = false },
  { .octave = e_O_3,    .note = e_D,     .length = e_L_1_8,     .legato = false },

  { .octave = e_O_3,    .note = e_C,     .length = e_L_1_4,     .legato = false },
  { .octave = e_O_3,    .note = e_C,     .length = e_L_1_8,     .legato = false },
  { .octave = e_O_3,    .note = e_Es,    .length = e_L_1_8,     .legato = false },

  { .octave = e_O_3,    .note = e_G,     .length = e_L_1_4,     .legato = false },
  { .octave = e_O_3,    .note = e_F,     .length = e_L_1_8,     .legato = false },
  { .octave = e_O_3,    .note = e_Es,    .length = e_L_1_8,     .legato = false },

  { .octave = e_O_3,    .note = e_D,     .length = e_L_1_4,     .legato = true  },
  { .octave = e_O_3,    .note = e_D,     .length = e_L_1_8,     .legato = false },
  { .octave = e_O_3,    .note = e_Es,    .length = e_L_1_8,     .legato = false },

  { .octave = e_O_3,    .note = e_F,     .length = e_L_1_4,     .legato = false },
  { .octave = e_O_3,    .note = e_G,     .length = e_L_1_4,     .legato = false },

  // Staccato
  { .octave = e_O_3,    .note = e_Es,    .length = e_L_1_8,     .legato = true  },
  { .octave = e_O_3,    .note = e_Es,    .length = e_L_1_16,    .legato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_16,    .legato = false },
  { .octave = e_O_3,    .note = e_C,     .length = e_L_1_8,     .legato = true  },
  { .octave = e_O_3,    .note = e_C,     .length = e_L_1_16,    .legato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_16,    .legato = false },

  { .octave = e_O_3,    .note = e_C,     .length = e_L_1_4,     .legato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_4,     .legato = false },


  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false },
  { .octave = e_O_3,    .note = e_F,     .length = e_L_1_8,     .legato = true  },
  { .octave = e_O_3,    .note = e_F,     .length = e_L_1_8,     .legato = false },
  { .octave = e_O_3,    .note = e_As,    .length = e_L_1_8,     .legato = false },

  { .octave = e_O_4,    .note = e_C,     .length = e_L_1_4,     .legato = false },
  { .octave = e_O_3,    .note = e_B,     .length = e_L_1_8,     .legato = false },
  { .octave = e_O_3,    .note = e_As,    .length = e_L_1_8,     .legato = false },

  { .octave = e_O_3,    .note = e_G,     .length = e_L_1_4,     .legato = true  },
  { .octave = e_O_3,    .note = e_G,     .length = e_L_1_8,     .legato = false },
  { .octave = e_O_3,    .note = e_Es,    .length = e_L_1_8,     .legato = false },

  { .octave = e_O_3,    .note = e_G,     .length = e_L_1_4,     .legato = false },
  { .octave = e_O_3,    .note = e_F,     .length = e_L_1_8,     .legato = false },
  { .octave = e_O_3,    .note = e_Es,    .length = e_L_1_8,     .legato = false },

  { .octave = e_O_3,    .note = e_D,     .length = e_L_1_4,     .legato = false },
  { .octave = e_O_3,    .note = e_D,     .length = e_L_1_8,     .legato = false },
  { .octave = e_O_3,    .note = e_Es,    .length = e_L_1_8,     .legato = false },

  { .octave = e_O_3,    .note = e_F,     .length = e_L_1_4,     .legato = false },
  { .octave = e_O_3,    .note = e_G,     .length = e_L_1_4,     .legato = false },

  // Staccato
  { .octave = e_O_3,    .note = e_Es,    .length = e_L_1_8,     .legato = true  },
  { .octave = e_O_3,    .note = e_Es,    .length = e_L_1_16,    .legato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_16,    .legato = false },
  { .octave = e_O_3,    .note = e_C,     .length = e_L_1_8,     .legato = true  },
  { .octave = e_O_3,    .note = e_C,     .length = e_L_1_16,    .legato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_16,    .legato = false },

  { .octave = e_O_3,    .note = e_C,     .length = e_L_1_4,     .legato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_4,     .legato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_EndMark, .legato = false },
};


t_melody melody= {
  .channel = 0,
  .tones = notes
};


void melodyInit() {
  psgAmplitude(melody.channel, 3);
  sequencerPlayMelody(&melody);
}


