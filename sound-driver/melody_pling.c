#include <stdbool.h>
#include <stddef.h>
#include "psg.h"
#include "sequencer.h"
#include "scheduler.h"
#include "config.h"


const t_tone plingVoice1[] = {
  { .octave = e_O_5,    .note = e_C,     .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_Cis,   .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_D,     .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_Dis,   .length = e_L_1_16,    .legato = false, .staccato = false },
  { .octave = e_O_5,    .note = e_E,     .length = e_L_1_8,     .legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_SyncMark,.legato = false, .staccato = false },
  { .octave = e_O_Null, .note = e_Null,  .length = e_L_StopMark,.legato = false, .staccato = false },

  { .octave = e_O_Null, .note = e_Null,  .length = e_L_EndMark, .legato = false, .staccato = false },
};

t_melodies pling = {
  .melodies = { { .tones = plingVoice1 } },
  .numOfMelodies = 1,
  .pace = 200,
  .chip = 1
};

void playPling() {
  pling.p_amplitude = configGetEffectsAmplitudePtr();
  sequencerPlayMelodies(&pling);
}



