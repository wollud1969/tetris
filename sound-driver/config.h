#ifndef _CONFIG_H_
#define _CONFIG_H_


#include <stdint.h>

void configSetAmplitude(uint8_t v);
uint8_t *configGetMelodyAmplitudePtr();
uint8_t *configGetEffectsAmplitudePtr();


#endif // _CONFIG_H_
