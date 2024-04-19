#ifndef _SPI_H_
#define _SPI_H_

#include <stdint.h>


typedef enum { e_SPI_CANVAS, e_SPI_DISPLAY, e_SPI_SOUND, e_SPI_EEPROM } t_SpiDeviceSelector;

void spiInit();
void spiSendBegin(t_SpiDeviceSelector d);
void spiSendEnd(t_SpiDeviceSelector d);
void spiSendOctet(uint8_t v); 
uint8_t spiReceiveOctet();



#endif // _SPI_H_
