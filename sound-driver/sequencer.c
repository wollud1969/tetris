#include "sequencer.h"
#include "scheduler.h"
#include "psg.h"



void sequencerInit() {
}

void sequencerExec(void *handle) {  
  t_melody *melody = (t_melody*) handle;

  switch (melody->state) {
    case e_PlayTone:
      if (melody->tones[melody->idx].length == e_L_EndMark) {
        melody->idx = 0;
      }

      psgPlayTone(melody->channel, melody->tones[melody->idx].octave, melody->tones[melody->idx].note);

      melody->lengthCnt = melody->tones[melody->idx].length;
      melody->state = e_HoldTone;
      break;
    case e_HoldTone:
      melody->lengthCnt -= 1;
      if (melody->lengthCnt == 0) {
        melody->state = e_SeparateTone;
      }
      break;
    case e_SeparateTone:
      if (! (melody->tones[melody->idx].legato)) {
        psgPlayTone(melody->channel, e_O_Null, e_Pause);
      }
      melody->idx += 1;
      melody->state = e_PlayTone;
      break;
  }
}

uint8_t sequencerPlayMelody(t_melody *melody) {
  melody->idx = 0;
  melody->lengthCnt = 0;
  melody->state = e_PlayTone;
  schAdd(sequencerExec, (void*) melody, 0, 10);
  return 0;
}

