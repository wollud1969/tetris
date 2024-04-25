#include <stdbool.h>
#include <stddef.h>
#include "psg.h"
#include "sequencer.h"
#include "scheduler.h"

const t_tone plingVoice1[] = {
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_4,     .legato = false, .staccato = true  },
  { .octave = e_O_5,    .note = e_G,     .length = e_L_1_4,     .legato = false, .staccato = true  },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Null,  .length = e_L_StopMark,.legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_EndMark, .legato = false, .staccato = false },
};

t_melodies pling = {
  .melodies = { { .amplitude = 12, .tones = plingVoice1 } },
  .numOfMelodies = 1,
  .pace = 200,
  .chip = 1
};

void playPling() {
  sequencerPlayMelodies(&pling);
}



