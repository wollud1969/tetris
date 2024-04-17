#ifndef _SOUND_H_
#define _SOUND_H_

#include <stdint.h>

#define MUTE_DELAY 30 // seconds

#include "../sound-driver/soundCodes.h"

void soundInit();
void soundCtrl(uint8_t cmd);



#endif // _SOUND_H_
