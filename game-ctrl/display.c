#include <stdint.h>

#include "display.h"
#include "spi.h"


uint16_t score;


void displayInit() {
  score = 0;

  spiSendBegin(e_SPI_DISPLAY);

  // display test off
  spiSendOctet(0x0f);
  spiSendOctet(0x01);

  // BCD decode for all digits
  spiSendOctet(0x09);
  spiSendOctet(0xff);

  // scan limit to digits 0-3
  spiSendOctet(0x0b);
  spiSendOctet(0x03);

  // intensity
  spiSendOctet(0x0a);
  spiSendOctet(0x0f);


  // normal operation
  spiSendOctet(0x0C);
  spiSendOctet(0x01);

  spiSendEnd(e_SPI_DISPLAY);
}



void displaySetScore(uint16_t v) {
  score = v;

  spiSendBegin(e_SPI_DISPLAY);

  spiSendOctet(0x01);
  spiSendOctet(0x07);

  spiSendEnd(e_SPI_DISPLAY);
}
