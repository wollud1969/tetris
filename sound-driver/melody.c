#include <stdbool.h>
#include "psg.h"
#include "sequencer.h"

/*
 * most simple Tetris from https://de.wikipedia.org/wiki/Korobeiniki
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
*/


/*
 * drei-stimmiges theme from https://www.gamemusicthemes.com/sheetmusic/gameboy/tetris/themea/Tetris_-_Theme_A_by_Gori_Fater.pdf
 */
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

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_D,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_4,     .legato = true,  .staccato = false }, // diese und die naechste zusammen: ein punktiertes Viertel
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_D,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_D,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_F,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_G,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_F,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_4,     .legato = true,  .staccato = false }, // punktiert
  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_D,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_D,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_4,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // -------
  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_D,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_D,     .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_D,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_4,     .legato = true,  .staccato = false }, // diese und die naechste zusammen: ein punktiertes Viertel
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_D,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_D,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_F,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_G,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_F,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_4,     .legato = true,  .staccato = false }, // punktiert
  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_D,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_D,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_4,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // -------
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_C,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_D,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_H,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_C,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_3,    .note = e_Gis,   .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_H,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_C,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_D,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_H,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_C,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1,       .legato = false, .staccato = false },
  
  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // -------
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_C,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_D,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_H,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_C,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_3,    .note = e_Gis,   .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_H,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_C,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_D,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_H,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_C,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1,       .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_EndMark, .legato = false, .staccato = false },
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

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_4,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_F,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_G,     .length = e_L_1_4,     .legato = true,  .staccato = false }, // punktiert
  { .octave = e_O_4,    .note = e_G,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_G,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_G,     .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_F,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_4,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // -------
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_4,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_F,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_G,     .length = e_L_1_4,     .legato = true,  .staccato = false }, // punktiert
  { .octave = e_O_4,    .note = e_G,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_G,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_G,     .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_F,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_4,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // -------
  { .octave = e_O_4,    .note = e_C,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_3,    .note = e_H,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_Gis,   .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_D,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_3,    .note = e_D,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_G,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_C,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_3,    .note = e_H,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_Gis,   .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_C,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_3,    .note = e_E,     .length = e_L_1,       .legato = false, .staccato = false },
  
  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // -------
  { .octave = e_O_4,    .note = e_C,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_3,    .note = e_H,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_Gis,   .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_D,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_3,    .note = e_D,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_G,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_4,    .note = e_C,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_3,    .note = e_H,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_Gis,   .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_C,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_3,    .note = e_E,     .length = e_L_1,       .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_EndMark, .legato = false, .staccato = false },
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

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_3,    .note = e_D,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_D,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_D,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_D,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_F,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_2,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_G,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_G,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_2,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_4,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // -------
  { .octave = e_O_2,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_3,    .note = e_D,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_D,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_D,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_D,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_F,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_2,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_G,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_G,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_2,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_4,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // -------
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
   
  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // -------
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_EndMark, .legato = false, .staccato = false },
};

t_melodies tetrisTheme = {
  .melodies = { { .amplitude = 3, .tones = tetris1 }, { .amplitude = 3, .tones = tetris2 }, { .amplitude = 3, .tones = tetris3 } },
  .numOfMelodies = 3,
  .pace = 4
};

void melodyInit() {
  sequencerPlayMelodies(&tetrisTheme);
}


