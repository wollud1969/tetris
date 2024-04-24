#include <stdint.h>
#include <stdbool.h>
#include <sys/param.h>
#include "sequencer.h"
#include "scheduler.h"
#include "psg.h"


uint8_t slots;

void sequencerInit() {
  slots = 0;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wswitch"
#pragma GCC diagnostic ignored "-Wreturn-type"
static uint16_t calcLength(t_melodies *m, t_noteLength l) {
  switch (l) {
    case e_L_1:
      return m->quarterLength << 2;
    case e_L_1_2:
      return m->quarterLength << 1;
    case e_L_1_4:
      return m->quarterLength;
    case e_L_1_8:
      return m->quarterLength >> 1;
    case e_L_1_16:
      return m->quarterLength >> 2;
    case e_L_1_32:
      return m->quarterLength >> 4;
  }
}
#pragma GCC diagnostic pop


void sequencerExec(void *handle) {  
  t_melodies *melodies = (t_melodies*) handle;

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
        } else if (melody->tones[melody->idx].length == e_L_HoldMark) {
          melody->state = e_Hold;
        } else if (melody->tones[melody->idx].length == e_L_StopMark) {
          melody->state = e_Terminate;
        } else {
          if (melody->tones[melody->idx].length == e_L_EndMark) {
            melody->idx = 0;
          }
          psgPlayTone(melodies->chip, channel, melody->amplitude, melody->tones[melody->idx].octave, melody->tones[melody->idx].note);
          melody->lengthCnt = (melody->tones[melody->idx].staccato) ? 
            (calcLength(melodies, melody->tones[melody->idx].length) / 2) : 
            calcLength(melodies, melody->tones[melody->idx].length);
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
        psgPlayTone(melodies->chip, channel, 0, e_O_Null, e_Pause);
        melody->lengthCnt = calcLength(melodies, melody->tones[melody->idx].length) / 2;
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
          psgPlayTone(melodies->chip, channel, 0, e_O_Null, e_Pause);
        }
        melody->idx += 1;
        melody->state = e_PlayTone;
        break;
      case e_Hold:
        break;
      case e_Terminate:
        schDel(melodies->taskId);
        slots &= ~(melodies->slotMask);
        break;
    }
  }
}

void sequencerPlayMelodies(t_melodies *melodies) {
  if ((slots & melodies->slotMask) != 0) {
    return;
  }

  slots |= melodies->slotMask;
  for (uint8_t i = 0; i < NUM_OF_CHANNELS; i++) {
    melodies->melodies[i].idx = 0;
    melodies->melodies[i].lengthCnt = 0;
    melodies->melodies[i].state = e_Init;
  }
  melodies->sync = 0;
  melodies->quarterLength = 60000 / melodies->pace / SEQUENCER_PERIOD; // duration of a 1/4 tone in ms

  melodies->taskId = schAdd(sequencerExec, (void*) melodies, 0, SEQUENCER_PERIOD);
}

void sequencerStopMelodies(t_melodies *melodies) {
  slots &= ~(melodies->slotMask);
  schDel(melodies->taskId);
}

void sequencerChangePace(t_melodies *melodies) {
  melodies->quarterLength = 60000 / melodies->pace / SEQUENCER_PERIOD; // duration of a 1/4 tone in ms
}

