#include <stdint.h>
#include "sound.h"
#include "spi.h"
#include "eeprom.h"



void soundInit() {
  soundCtrl(SOUND_COMMAND + SOUND_SUBCMD_AMPLITUDE + eepromReadAmplitude());
}


void soundCtrl(uint8_t cmd) {
  spiSendBegin(e_SPI_SOUND);

  spiSendOctet(cmd);

  spiSendEnd(e_SPI_SOUND);
}

