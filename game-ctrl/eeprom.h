#ifndef _EEPROM_H_
#define _EEPROM_H_

#include <stdint.h>


void eepromInit();
uint16_t eepromReadHighScore();
void eepromWriteHighScore(uint16_t v);



#endif // _EEPROM_H_
