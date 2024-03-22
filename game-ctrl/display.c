#include <stdint.h>

#include "display.h"
#include "spi.h"



void displayInit() {
}


void displaySetValue(uint16_t v) {
  union {
    uint16_t value;
    uint8_t sendBuffer[2];
  } value;

  value.value = v;

  spiSendBegin(e_SPI_DISPLAY);

  spiSendOctet(value.sendBuffer[0]);
  spiSendOctet(value.sendBuffer[1]);

  spiSendEnd(e_SPI_DISPLAY);
}
