#include "sequencer.h"
#include "scheduler.h"
#include "psg.h"


void sequencerInit() {
}

void sequencerExec(void *handle) {  
  t_melody *melody = (t_melody*) handle;

  if (melody->lengthCnt == 0) {
    if (melody->tones[melody->idx].length == e_L_EndMark) {
      melody->idx = 0;
    }

    psgPlayTone(melody->channel, melody->tones[melody->idx].octave, melody->tones[melody->idx].note);

    melody->lengthCnt = melody->tones[melody->idx].length;
    melody->idx += 1;
  }

  melody->lengthCnt -= 1;
}

uint8_t sequencerPlayMelody(t_melody *melody) {
  melody->idx = 0;
  melody->lengthCnt = 0;
  schAdd(sequencerExec, (void*) melody, 0, 25);
  return 0;
}

