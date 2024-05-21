#ifndef _EEPROM_H_
#define _EEPROM_H_

#include <stdint.h>


void eepromInit();
void eepromCommit();
void eepromShowValues();
uint16_t eepromReadHighScore();
void eepromSetHighScore(uint16_t v);
uint8_t eepromReadFlashColor();
void eepromSetFlashColor(uint8_t v);
uint8_t eepromReadBrightness();
void eepromSetBrightness(uint8_t v);
uint8_t eepromReadAmplitude();
void eepromSetAmplitude(uint8_t v);
void eepromIncGameCounter();
uint16_t eepromReadGameCounter();
void eepromClearGameCounter();



#endif // _EEPROM_H_
