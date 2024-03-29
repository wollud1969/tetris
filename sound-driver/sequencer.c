#include <sys/param.h>
#include "sequencer.h"
#include "scheduler.h"
#include "psg.h"



void sequencerInit() {
}

void sequencerExec(void *handle) {  
  t_melodies *melodies = (t_melodies*) handle;

  for (uint8_t channel = 0; channel < MAX(NUM_OF_CHANNELS, melodies->numOfMelodies); channel++) {
    t_melody *melody = &(melodies->melodies[channel]);

    switch (melody->state) {
      case e_Init:
        psgAmplitude(channel, melody->amplitude);
        melody->state = e_PlayTone;
        break;
      case e_PlayTone:
        if (melody->tones[melody->idx].length == e_L_EndMark) {
          melody->idx = 0;
        }
        psgPlayTone(channel, melody->tones[melody->idx].octave, melody->tones[melody->idx].note);
        melody->lengthCnt = (melody->tones[melody->idx].staccato) ? (melody->tones[melody->idx].length / 2) : melody->tones[melody->idx].length;
        melody->state = e_HoldTone;
        break;
      case e_HoldTone:
        melody->lengthCnt -= 1;
        if (melody->lengthCnt == 0) {
          melody->state = (melody->tones[melody->idx].staccato) ? e_StaccatoBreak : e_SeparateTone;
        }
        break;
      case e_StaccatoBreak:
        psgPlayTone(channel, e_O_Null, e_Pause);
        melody->lengthCnt = melody->tones[melody->idx].length / 2;
        melody->state = e_HoldStaccatoBreak;
        break;
      case e_HoldStaccatoBreak:
        melody->lengthCnt -= 1;
        if (melody->lengthCnt == 0) {
          melody->state = e_SeparateTone;
        }
        break;
      case e_SeparateTone:
        if (! (melody->tones[melody->idx].legato)) {
          psgPlayTone(channel, e_O_Null, e_Pause);
        }
        melody->idx += 1;
        melody->state = e_PlayTone;
        break;
    }
  }
}

uint16_t sequencerPlayMelodies(t_melodies *melodies) {
  for (uint8_t i = 0; i < NUM_OF_CHANNELS; i++) {
    melodies->melodies[i].idx = 0;
    melodies->melodies[i].lengthCnt = 0;
    melodies->melodies[i].state = e_Init;
  }

  return schAdd(sequencerExec, (void*) melodies, 0, melodies->pace);
}

