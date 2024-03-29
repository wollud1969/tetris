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
 * three voices theme from https://www.gamemusicthemes.com/sheetmusic/gameboy/tetris/themea/Tetris_-_Theme_A_by_Gori_Fater.pdf
 */
const t_tone voice1[] = {
  // -------
  // 1. beat
  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_D,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_D,     .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 2. beat
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_D,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 3. beat
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_4,     .legato = true,  .staccato = false }, // diese und die naechste zusammen: ein punktiertes Viertel
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_D,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 4. beat
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 5. beat
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_D,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_F,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_G,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_F,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 6. beat
  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_4,     .legato = true,  .staccato = false }, // punktiert
  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_D,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 7. beat
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_D,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 8. beat
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_4,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // -------
  // 1. beat, repeat
  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_D,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_D,     .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 2. beat, repeat
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_D,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 3. beat, repeat
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_4,     .legato = true,  .staccato = false }, // diese und die naechste zusammen: ein punktiertes Viertel
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_D,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 4. beat, repeat
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 5. beat, repeat
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_D,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_F,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_G,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_F,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 6. beat, repeat
  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_4,     .legato = true,  .staccato = false }, // punktiert
  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_D,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 7. beat, repeat
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_D,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 8. beat, repeat
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_4,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // -------
  // 9. beat
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_C,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 10. beat
  { .octave = e_O_4,    .note = e_D,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_H,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 11. beat
  { .octave = e_O_4,    .note = e_C,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 12. beat
  { .octave = e_O_3,    .note = e_Gis,   .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_H,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 13. beat
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_C,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 14. beat
  { .octave = e_O_4,    .note = e_D,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_H,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 15. beat
  { .octave = e_O_4,    .note = e_C,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 16. beat
  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1,       .legato = false, .staccato = false },
  
  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // -------
  // 9. beat, repeat
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_C,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 10. beat, repeat
  { .octave = e_O_4,    .note = e_D,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_H,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 11. beat, repeat
  { .octave = e_O_4,    .note = e_C,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 12. beat, repeat
  { .octave = e_O_3,    .note = e_Gis,   .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_H,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 13. beat, repeat
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_C,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 14. beat, repeat
  { .octave = e_O_4,    .note = e_D,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_H,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 15. beat, repeat
  { .octave = e_O_4,    .note = e_C,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 16. beat, repeat
  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1,       .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_EndMark, .legato = false, .staccato = false },
};

const t_tone voice2[] = {
  // -------
  // 1. beat
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 2. beat
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 3. beat
  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_4,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 4. beat
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 5. beat
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_F,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 6. beat
  { .octave = e_O_4,    .note = e_G,     .length = e_L_1_4,     .legato = true,  .staccato = false }, // punktiert
  { .octave = e_O_4,    .note = e_G,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_G,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_G,     .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_F,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 7. beat
  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 8. beat
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_4,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // -------
  // 1. beat, repeat
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 2. beat, repeat
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 3. beat, repeat
  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_4,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 4. beat, repeat
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 5. beat, repeat
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_F,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 6. beat, repeat
  { .octave = e_O_4,    .note = e_G,     .length = e_L_1_4,     .legato = true,  .staccato = false }, // punktiert
  { .octave = e_O_4,    .note = e_G,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_G,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_G,     .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_F,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 7. beat, repeat
  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 8. beat, repeat
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_4,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // -------
  // 9. beat
  { .octave = e_O_4,    .note = e_C,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 10. beat
  { .octave = e_O_3,    .note = e_H,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_Gis,   .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 11. beat
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_D,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 12. beat
  { .octave = e_O_3,    .note = e_D,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_G,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 13. beat
  { .octave = e_O_4,    .note = e_C,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 14. beat
  { .octave = e_O_3,    .note = e_H,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_Gis,   .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 15. beat
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_C,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 16. beat
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1,       .legato = false, .staccato = false },
  
  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // -------
  // 9. beat, repeat
  { .octave = e_O_4,    .note = e_C,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 10. beat, repeat
  { .octave = e_O_3,    .note = e_H,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_Gis,   .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 11. beat, repeat
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_D,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 12. beat, repeat
  { .octave = e_O_3,    .note = e_D,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_G,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 13. beat, repeat
  { .octave = e_O_4,    .note = e_C,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 14. beat, repeat
  { .octave = e_O_3,    .note = e_H,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_Gis,   .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 15. beat, repeat
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_C,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 16. beat, repeat
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1,       .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_EndMark, .legato = false, .staccato = false },
};

const t_tone voice3[] = {
  // -------
  // 1. beat
  { .octave = e_O_2,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 2. beat
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 3. beat
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 4. beat
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 5. beat
  { .octave = e_O_3,    .note = e_D,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_D,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_D,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_D,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_F,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 6. beat
  { .octave = e_O_2,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_G,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_G,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 7. beat
  { .octave = e_O_2,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 8. beat
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_4,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // -------
  // 1. beat,repeat
  { .octave = e_O_2,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 2. beat,repeat
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 3. beat,repeat
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 4. beat,repeat
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 5. beat,repeat
  { .octave = e_O_3,    .note = e_D,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_D,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_D,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_D,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_F,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 6. beat,repeat
  { .octave = e_O_2,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_G,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_G,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 7. beat,repeat
  { .octave = e_O_2,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 8. beat,repeat
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_4,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // -------
  // 9. beat
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 10. beat
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 11. beat
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 12. beat
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 13. beat
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 14. beat
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 15. beat
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 16. beat
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
  // 9. beat, repeat
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 10. beat, repeat
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 11. beat, repeat
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 12. beat, repeat
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 13. beat, repeat
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 14. beat, repeat
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 15. beat, repeat
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 16. beat, repeat
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
  .melodies = { { .amplitude = 3, .tones = voice1 }, { .amplitude = 3, .tones = voice2 }, { .amplitude = 3, .tones = voice3 } },
  .numOfMelodies = 3,
  .pace = 160
};

void melodyInit() {
  sequencerPlayMelodies(&tetrisTheme);
}


