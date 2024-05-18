#include <stdint.h>
#include "eeprom.h"
#include "spi.h"


#define MAGIC 0xafff
#define HIGHSCORE_ADDR 0x00
#define DUMMY 0x00
#define CMD_READ  0b00000011
#define CMD_WRITE 0b00000010
#define CMD_WRDI  0b00000100
#define CMD_WREN  0b00000110


typedef struct {
  uint16_t magic;
  uint16_t highScore;
  uint8_t flashColor;
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
    buf.v.magic = MAGIC;
    buf.v.highScore = 0;
    buf.v.flashColor = 0;
    writeBuf();
  }
}

void eepromCommit() {
  writeBuf();
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

