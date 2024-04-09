#include <stdint.h>
#include <stdbool.h>
#include <sys/param.h>
#include "sequencer.h"
#include "scheduler.h"
#include "psg.h"



void sequencerInit() {
}

void sequencerExec(void *handle) {  
  static uint16_t lengths[e_L_LengthEnd];
  t_melodies *melodies = (t_melodies*) handle;

  if (melodies->firstRun) {
    melodies->firstRun = false;

    lengths[e_L_1_4]  = 60000 / melodies->pace; // duration of a 1/4 tone in ms
    lengths[e_L_1_2]  = lengths[e_L_1_4] << 1;
    lengths[e_L_1]    = lengths[e_L_1_4] << 2;
    lengths[e_L_1_8]  = lengths[e_L_1_4] >> 1;
    lengths[e_L_1_16] = lengths[e_L_1_4] >> 2;
    lengths[e_L_1_32] = lengths[e_L_1_4] >> 4;

    for (uint8_t i = 0; i < e_L_LengthEnd; i++) {
      lengths[i] /= SEQUENCER_PERIOD;
    }
  }

  for (uint8_t channel = 0; channel < melodies->numOfMelodies; channel++) {
    t_melody *melody = &(melodies->melodies[channel]);

    switch (melody->state) {
      case e_Init:
        melody->state = e_PlayTone;
        break;
      case e_PlayTone:
        if (melody->tones[melody->idx].length == e_L_SyncMark) {
          if (melodies->sync == 0) {
            melodies->sync = melodies->numOfMelodies;
          }
          melodies->sync -= 1;
          melody->state = e_Sync;
        } else if (melody->tones[melody->idx].length == e_L_StopMark) {
          melody->state = e_Terminate;
        } else {
          if (melody->tones[melody->idx].length == e_L_EndMark) {
            melody->idx = 0;
          }
          psgPlayTone(melody->chip, channel, melody->amplitude, melody->tones[melody->idx].octave, melody->tones[melody->idx].note);
          melody->lengthCnt = (melody->tones[melody->idx].staccato) ? (lengths[melody->tones[melody->idx].length] / 2) : lengths[melody->tones[melody->idx].length];
          melody->state = e_HoldTone;
        }
        break;
      case e_Sync:
        if (melodies->sync == 0) {
          melody->state = e_SeparateTone;
        }
        break;
      case e_HoldTone:
        melody->lengthCnt -= 1;
        if (melody->lengthCnt == 0) {
          melody->state = (melody->tones[melody->idx].staccato) ? e_StaccatoBreak : e_SeparateTone;
        }
        break;
      case e_StaccatoBreak:
        psgPlayTone(melody->chip, channel, 0, e_O_Null, e_Pause);
        melody->lengthCnt = lengths[melody->tones[melody->idx].length] / 2;
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
          psgPlayTone(melody->chip, channel, 0, e_O_Null, e_Pause);
        }
        melody->idx += 1;
        melody->state = e_PlayTone;
        break;
      case e_Terminate:
        schDel(melodies->taskId);
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
  melodies->sync = 0;
  melodies->firstRun = true;

  melodies->taskId = schAdd(sequencerExec, (void*) melodies, 0, SEQUENCER_PERIOD);

  return melodies->taskId;
}

