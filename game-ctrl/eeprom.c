#include <stdint.h>
#include <string.h>
#include <sys/param.h>
#include "eeprom.h"
#include "spi.h"
#include "scheduler.h"
#include "display.h"
#include "canvas.h"
#include "../rgb-driver/colors.h"


#define MAGIC 0xb003
#define HIGHSCORE_ADDR 0x00
#define DUMMY 0x00
#define CMD_READ  0b00000011
#define CMD_WRITE 0b00000010
#define CMD_WRDI  0b00000100
#define CMD_WREN  0b00000110


typedef struct {
  uint16_t magic;
  uint16_t highScore;
  uint16_t gameCounter;
  uint8_t flashColor;
  uint8_t brightness;
  uint8_t amplitude;
} t_configBlock;

typedef union {
  t_configBlock v;
  uint8_t buffer[sizeof(t_configBlock)];
} eepromBuf_t;

eepromBuf_t buf;

static void writeBuf() {
  spiSendBegin(e_SPI_EEPROM);
  spiSendOctet(CMD_WREN);
  spiSendEnd(e_SPI_EEPROM);

  spiSendBegin(e_SPI_EEPROM);
  spiSendOctet(CMD_WRITE);
  spiSendOctet(HIGHSCORE_ADDR);
  for (uint8_t i = 0; i < sizeof(t_configBlock); i++) {
    spiSendOctet(buf.buffer[i]);
  }
  spiSendEnd(e_SPI_EEPROM);
}

static void readBuf() {
  spiSendBegin(e_SPI_EEPROM);
  spiSendOctet(CMD_READ);
  spiReceiveOctet();
  spiSendOctet(HIGHSCORE_ADDR);
  spiReceiveOctet();
  for (uint8_t i = 0; i < sizeof(t_configBlock); i++) {
    spiSendOctet(DUMMY);
    buf.buffer[i] = spiReceiveOctet();
  }
  spiSendEnd(e_SPI_EEPROM);
}

void eepromInit() {
  readBuf();

  if (buf.v.magic != MAGIC) {
    memset(buf.buffer, 0, sizeof(t_configBlock));
    buf.v.magic = MAGIC;
    writeBuf();
  }
}

void eepromCommit() {
  writeBuf();
}


void eepromShowValues() {
  canvasClear();
  canvasFillRow(0, _green);
  canvasShow();
  displaySetValue(buf.v.highScore);
  wait(2);
  canvasClear();
  canvasFillRow(1, _green);
  canvasShow();
  displaySetValue(MIN(buf.v.gameCounter, 9999));
  wait(2);
  canvasClear();
  canvasFillRow(2, _green);
  canvasShow();
  displaySetValue(buf.v.flashColor);
  wait(2);
  canvasClear();
  canvasFillRow(3, _green);
  canvasShow();
  displaySetValue(buf.v.brightness);
  wait(2);
  canvasClear();
  canvasFillRow(4, _green);
  canvasShow();
  displaySetValue(buf.v.amplitude);
  wait(2);
}

uint16_t eepromReadHighScore() {
  return buf.v.highScore;
}

void eepromSetHighScore(uint16_t v) {
  buf.v.highScore = v;
  writeBuf();
}

uint8_t eepromReadFlashColor() {
  return buf.v.flashColor;
}

void eepromSetFlashColor(uint8_t v) {
  buf.v.flashColor = v;
}

uint8_t eepromReadBrightness() {
  return buf.v.brightness;
}

void eepromSetBrightness(uint8_t v) {
  buf.v.brightness = v;
}

uint8_t eepromReadAmplitude() {
  return buf.v.amplitude;
}

void eepromSetAmplitude(uint8_t v) {
  buf.v.amplitude = v;
}

void eepromIncGameCounter() {
  buf.v.gameCounter += 1;
  writeBuf();
}


