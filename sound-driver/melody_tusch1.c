#include <stdbool.h>
#include <stddef.h>
#include "psg.h"
#include "sequencer.h"
#include "scheduler.h"
#include "melody_tetris.h"

const t_tone tusch1voice1[] = {
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_4,     .legato = false, .staccato = true  },
  { .octave = e_O_5,    .note = e_F,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_4,     .legato = false, .staccato = true  },
  { .octave = e_O_5,    .note = e_F,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_4,     .legato = false, .staccato = true  },
  { .octave = e_O_5,    .note = e_F,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Null,  .length = e_L_StopMark,.legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_EndMark, .legato = false, .staccato = false },
};

const t_tone tusch1voice2[] = {
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Null,  .length = e_L_HoldMark,.legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_EndMark, .legato = false, .staccato = false },
};

const t_tone tusch1voice3[] = {
  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_8,     .legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Pause, .length = e_L_1_4,     .legato = false, .staccato = false },
  { .octave = e_O_4,    .note = e_A,     .length = e_L_1_2,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Null,  .length = e_L_HoldMark,.legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_EndMark, .legato = false, .staccato = false },
};

t_melodies tusch1 = {
  .melodies = { { .chip = 1, .amplitude = 12, .tones = tusch1voice1 }, { .chip = 1, .amplitude = 12, .tones = tusch1voice2 }, { .chip = 1, .amplitude = 12, .tones = tusch1voice3 } },
  .numOfMelodies = 3,
  .pace = 200,
  .slotMask = 0x02
};

void playTusch1() {
  sequencerPlayMelodies(&tusch1);
  playMelodyTetrisFaster();
}



