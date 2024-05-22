#include <stdbool.h>
#include <stddef.h>
#include "psg.h"
#include "sequencer.h"
#include "scheduler.h"
#include "config.h"


/*
 * three voices theme from https://www.gamemusicthemes.com/sheetmusic/gameboy/tetris/themea/Tetris_-_Theme_A_by_Gori_Fater.pdf
 */
const t_tone voice1[] = {
  // -------
  // 1. bar
  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_D,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_D,     .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 2. bar
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_D,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 3. bar
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_4,     .legato = true,  .staccato = false }, // diese und die naechste zusammen: ein punktiertes Viertel
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_D,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 4. bar
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 5. bar
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_D,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_F,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_G,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_F,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 6. bar
  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_4,     .legato = true,  .staccato = false }, // punktiert
  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_D,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 7. bar
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_D,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 8. bar
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_4,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // -------
  // 1. bar, repeat
  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_D,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_D,     .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 2. bar, repeat
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_D,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 3. bar, repeat
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_4,     .legato = true,  .staccato = false }, // diese und die naechste zusammen: ein punktiertes Viertel
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_D,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 4. bar, repeat
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 5. bar, repeat
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_D,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_F,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_G,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_F,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 6. bar, repeat
  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_4,     .legato = true,  .staccato = false }, // punktiert
  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_D,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 7. bar, repeat
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_D,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 8. bar, repeat
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_4,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // -------
  // 9. bar
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_C,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 10. bar
  { .octave = e_O_4,    .note = e_D,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_H,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 11. bar
  { .octave = e_O_4,    .note = e_C,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 12. bar
  { .octave = e_O_3,    .note = e_Gis,   .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_H,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 13. bar
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_C,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 14. bar
  { .octave = e_O_4,    .note = e_D,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_H,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 15. bar
  { .octave = e_O_4,    .note = e_C,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 16. bar
  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1,       .legato = false, .staccato = false },
  
  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // -------
  // 9. bar, repeat
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_C,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 10. bar, repeat
  { .octave = e_O_4,    .note = e_D,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_H,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 11. bar, repeat
  { .octave = e_O_4,    .note = e_C,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 12. bar, repeat
  { .octave = e_O_3,    .note = e_Gis,   .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_H,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 13. bar, repeat
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_C,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 14. bar, repeat
  { .octave = e_O_4,    .note = e_D,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_H,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 15. bar, repeat
  { .octave = e_O_4,    .note = e_C,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 16. bar, repeat
  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1,       .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_EndMark, .legato = false, .staccato = false },
};

const t_tone voice2[] = {
  // -------
  // 1. bar
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 2. bar
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 3. bar
  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_4,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 4. bar
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 5. bar
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_F,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 6. bar
  { .octave = e_O_4,    .note = e_G,     .length = e_L_1_4,     .legato = true,  .staccato = false }, // punktiert
  { .octave = e_O_4,    .note = e_G,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_G,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_G,     .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_F,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 7. bar
  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 8. bar
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_4,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // -------
  // 1. bar, repeat
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 2. bar, repeat
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 3. bar, repeat
  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_4,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 4. bar, repeat
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 5. bar, repeat
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_F,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 6. bar, repeat
  { .octave = e_O_4,    .note = e_G,     .length = e_L_1_4,     .legato = true,  .staccato = false }, // punktiert
  { .octave = e_O_4,    .note = e_G,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_G,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_G,     .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_F,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 7. bar, repeat
  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 8. bar, repeat
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_E,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_4,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // -------
  // 9. bar
  { .octave = e_O_4,    .note = e_C,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 10. bar
  { .octave = e_O_3,    .note = e_H,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_Gis,   .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 11. bar
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 12. bar
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_Gis,   .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 13. bar
  { .octave = e_O_4,    .note = e_C,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 14. bar
  { .octave = e_O_3,    .note = e_H,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_Gis,   .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 15. bar
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_C,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 16. bar
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1,       .legato = false, .staccato = false },
  
  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // -------
  // 9. bar, repeat
  { .octave = e_O_4,    .note = e_C,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 10. bar, repeat
  { .octave = e_O_3,    .note = e_H,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_Gis,   .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 11. bar, repeat
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 12. bar, repeat
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_Gis,   .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 13. bar, repeat
  { .octave = e_O_4,    .note = e_C,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 14. bar, repeat
  { .octave = e_O_3,    .note = e_H,     .length = e_L_1_2,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_Gis,   .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 15. bar, repeat
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_C,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 16. bar, repeat
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1,       .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_EndMark, .legato = false, .staccato = false },
};

const t_tone voice3[] = {
  // -------
  // 1. bar
  { .octave = e_O_2,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 2. bar
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 3. bar
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 4. bar
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 5. bar
  { .octave = e_O_3,    .note = e_D,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_D,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_D,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_D,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_F,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 6. bar
  { .octave = e_O_2,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_G,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_G,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 7. bar
  { .octave = e_O_2,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 8. bar
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_4,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // -------
  // 1. bar,repeat
  { .octave = e_O_2,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 2. bar,repeat
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 3. bar,repeat
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 4. bar,repeat
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 5. bar,repeat
  { .octave = e_O_3,    .note = e_D,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_D,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_D,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_D,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_F,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 6. bar,repeat
  { .octave = e_O_2,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_C,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_G,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_G,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 7. bar,repeat
  { .octave = e_O_2,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_H,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 8. bar,repeat
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_4,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // -------
  // 9. bar
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 10. bar
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 11. bar
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 12. bar
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 13. bar
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 14. bar
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 15. bar
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 16. bar
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
  // 9. bar, repeat
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 10. bar, repeat
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 11. bar, repeat
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 12. bar, repeat
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 13. bar, repeat
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 14. bar, repeat
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_Gis,   .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 15. bar, repeat
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_2,    .note = e_A,     .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_3,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  // 16. bar, repeat
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

#define INITIAL_PACE 160
t_melodies tetrisTheme = {
  .melodies = { { .tones = voice1 }, { .tones = voice2 }, { .tones = voice3 } },
  .numOfMelodies = 3,
  .pace = INITIAL_PACE,
  .chip = 0
};

void playMelodyTetris() {
  tetrisTheme.pace = INITIAL_PACE; // reset to start value each time
  tetrisTheme.p_amplitude = configGetMelodyAmplitudePtr();
  sequencerPlayMelodies(&tetrisTheme);
}

void playMelodyTetrisFaster() {
  tetrisTheme.pace += 15;
  sequencerChangePace(&tetrisTheme);
}

void stopMelodyTetris() {
  sequencerStopMelodies(&tetrisTheme);
}



