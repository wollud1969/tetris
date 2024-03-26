#include "sequencer.h"
#include "scheduler.h"
#include "psg.h"


void sequencerInit() {
}

void sequencerExec(void *handle) {  
  t_melody *melody = (t_melody*) handle;

  switch (melody->state) {
    case 0:
      if (melody->tones[melody->idx].length == e_L_EndMark) {
        melody->idx = 0;
      }

      psgPlayTone(melody->channel, melody->tones[melody->idx].octave, melody->tones[melody->idx].note);

      melody->lengthCnt = melody->tones[melody->idx].length;
      melody->state = 1;
      break;
    case 1:
      melody->lengthCnt -= 1;
      if (melody->lengthCnt == 0) {
        melody->state = 2;
      }
      break;
    case 2:
      if (! (melody->tones[melody->idx].legato)) {
        psgPlayTone(melody->channel, e_O_Null, e_Pause);
      }
      melody->idx += 1;
      melody->state = 0;
      break;
  }
}

uint8_t sequencerPlayMelody(t_melody *melody) {
  melody->idx = 0;
  melody->lengthCnt = 0;
  melody->state = 0;
  schAdd(sequencerExec, (void*) melody, 0, 10);
  return 0;
}

