#include "sound.h"
#include "spi.h"



void soundInit() {
}


void soundCtrl(t_SoundCmd cmd) {
  spiSendBegin(e_SPI_SOUND);

  spiSendOctet((uint8_t)cmd);

  spiSendEnd(e_SPI_SOUND);
}

