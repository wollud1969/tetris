#include "effects.h"
#include "psg.h"


void effectsInit() {

}


void playEffect1() {
  psgWrite(1, NOISE_PERIOD_REG, 0);
  psgWrite(1, _ENABLE_REG, psgReadShadow(1, _ENABLE_REG) & ~0b00111000);
  psgWrite(1, CHANNEL_A_AMPLITUDE_REG, 020);
  psgWrite(1, CHANNEL_B_AMPLITUDE_REG, 020);
  psgWrite(1, CHANNEL_C_AMPLITUDE_REG, 020);
  psgWrite(1, ENVELOPE_PERIOD_COARSE_REG, 070);
  psgWrite(1, ENVELOPE_SHAPE_REG, 0);
}
