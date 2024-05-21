#include <stdint.h>
#include "config.h"


typedef struct {
  uint8_t amplitude;
} config_t;

config_t config;


void configSetAmplitude(uint8_t v) {
  config.amplitude = v;
}

uint8_t configGetAmplitude() {
  return config.amplitude;
}

