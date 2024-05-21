#include <stdint.h>
#include <sys/param.h>
#include "config.h"


typedef struct {
  uint8_t melodyAmplitude;
  uint8_t effectsAmplitude;
} config_t;

config_t config;


void configSetAmplitude(uint8_t v) {
  config.melodyAmplitude = MIN(v, 15);
  config.effectsAmplitude = MIN(v+4, 15);
}

uint8_t *configGetMelodyAmplitudePtr() {
  return &(config.melodyAmplitude);
}

uint8_t *configGetEffectsAmplitudePtr() {
  return &(config.effectsAmplitude);
}

