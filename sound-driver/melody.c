#include <stdbool.h>
#include "psg.h"
#include "sequencer.h"


const t_tone notes[] = {
  { .octave = e_O_3,    .note = e_G,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_D,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_Es,    .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_3,    .note = e_F,     .length = e_L_1_4,     .legato = false, .staccato = false },
  // Triller
  { .octave = e_O_3,    .note = e_Es,    .length = e_L_1_32,    .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_F,     .length = e_L_1_32,    .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_Es,    .length = e_L_1_32,    .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_F,     .length = e_L_1_32,    .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_D,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_3,    .note = e_C,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_Es,    .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_3,    .note = e_G,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_F,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_Es,    .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_3,    .note = e_D,     .length = e_L_1_4,     .legato = true , .staccato = false },
  { .octave = e_O_3,    .note = e_D,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_Es,    .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_3,    .note = e_F,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_G,     .length = e_L_1_4,     .legato = false, .staccato = false },

  { .octave = e_O_3,    .note = e_Es,    .length = e_L_1_4,     .legato = false, .staccato = true  },
  { .octave = e_O_3,    .note = e_C,     .length = e_L_1_4,     .legato = false, .staccato = true  },

  { .octave = e_O_3,    .note = e_C,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_4,     .legato = false, .staccato = false },


  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_F,     .length = e_L_1_8,     .legato = true , .staccato = false },
  { .octave = e_O_3,    .note = e_F,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_As,    .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_C,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_B,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_As,    .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_3,    .note = e_G,     .length = e_L_1_4,     .legato = true , .staccato = false },
  { .octave = e_O_3,    .note = e_G,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_Es,    .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_3,    .note = e_G,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_F,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_Es,    .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_3,    .note = e_D,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_D,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_Es,    .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_3,    .note = e_F,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_G,     .length = e_L_1_4,     .legato = false, .staccato = false },

  { .octave = e_O_3,    .note = e_Es,    .length = e_L_1_4,     .legato = false, .staccato = true  },
  { .octave = e_O_3,    .note = e_C,     .length = e_L_1_4,     .legato = false, .staccato = true  },

  { .octave = e_O_3,    .note = e_C,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_4,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_EndMark, .legato = false, .staccato = false },
};


const t_tone tetris1[] = {
  // -------
  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_D,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_D,     .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_D,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_4,     .legato = true,  .staccato = false }, // diese und die naechste zusammen: ein punktiertes Viertel
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_D,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },

  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_D,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_F,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_G,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_F,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_4,     .legato = true,  .staccato = false }, // punktiert
  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_D,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_D,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },

  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_4,     .legato = false, .staccato = false },

  // -------
  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_D,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_D,     .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_D,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_4,     .legato = true,  .staccato = false }, // diese und die naechste zusammen: ein punktiertes Viertel
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_D,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },

  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_D,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_F,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_G,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_F,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_4,     .legato = true,  .staccato = false }, // punktiert
  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_D,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_D,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },

  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_4,     .legato = false, .staccato = false },

  // -------
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_C,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_D,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_H,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_C,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_3,    .note = e_Gis,   .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_H,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_C,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_D,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_H,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_C,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1,       .legato = false, .staccato = false },
  
  // -------
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_C,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_D,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_H,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_C,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_3,    .note = e_Gis,   .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_H,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_C,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_D,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_H,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_C,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1,       .legato = false, .staccato = false },
};

const t_tone tetris2[] = {
  // -------
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_4,     .legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_F,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_G,     .length = e_L_1_4,     .legato = true,  .staccato = false }, // punktiert
  { .octave = e_O_4,    .note = e_G,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_G,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_G,     .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_F,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_4,     .legato = false, .staccato = false },

  // -------
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_4,     .legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_F,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_G,     .length = e_L_1_4,     .legato = true,  .staccato = false }, // punktiert
  { .octave = e_O_4,    .note = e_G,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_G,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_G,     .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_F,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_4,     .legato = false, .staccato = false },

  // -------
  { .octave = e_O_4,    .note = e_C,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_3,    .note = e_H,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_Gis,   .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_D,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_3,    .note = e_D,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_G,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_C,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_3,    .note = e_H,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_Gis,   .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_C,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_3,    .note = e_E,     .length = e_L_1,       .legato = false, .staccato = false },
  
  // -------
  { .octave = e_O_4,    .note = e_C,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_3,    .note = e_H,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_Gis,   .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_D,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_3,    .note = e_D,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_G,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_C,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_3,    .note = e_H,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_Gis,   .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_C,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_3,    .note = e_E,     .length = e_L_1,       .legato = false, .staccato = false },
};

const t_tone tetris3[] = {
  // -------
  { .octave = e_O_2,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_3,    .note = e_D,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_D,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_D,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_D,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_F,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_2,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_G,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_G,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_2,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_4,     .legato = false, .staccato = false },

  // -------
  { .octave = e_O_2,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_3,    .note = e_D,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_D,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_D,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_D,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_F,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_2,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_G,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_G,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_2,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_4,     .legato = false, .staccato = false },

  // -------
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
   
  // -------
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
};

t_melody melody = {
  .pace = 4,
  .amplitude = 3,
  .channel = 0,
  .tones = notes
};


t_melody melodyTetris1 = {
  .pace = 4,
  .amplitude = 3,
  .channel = 0,
  .tones = tetris1
};
t_melody melodyTetris2 = {
  .pace = 4,
  .amplitude = 3,
  .channel = 1,
  .tones = tetris2
};
t_melody melodyTetris3 = {
  .pace = 4,
  .amplitude = 3,
  .channel = 1,
  .tones = tetris3
};


void melodyInit() {
  sequencerPlayMelody(&melodyTetris1);
  sequencerPlayMelody(&melodyTetris2);
  sequencerPlayMelody(&melodyTetris3);
}


