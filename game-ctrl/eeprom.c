#include <stdint.h>
#include "eeprom.h"
#include "spi.h"


#define MAGIC 0xaffe
#define HIGHSCORE_ADDR 0x00
#define DUMMY 0x00
#define CMD_READ  0b00000011
#define CMD_WRITE 0b00000010
#define CMD_WRDI  0b00000100
#define CMD_WREN  0b00000110


typedef union {
  uint8_t buffer[4];
  struct {
    uint16_t magic;
    uint16_t highScore;
  } v;
} eepromBuf_t;

eepromBuf_t buf;

static void writeBuf() {
  spiSendBegin(e_SPI_EEPROM);
  spiSendOctet(CMD_WREN);
  spiSendEnd(e_SPI_EEPROM);

  spiSendBegin(e_SPI_EEPROM);
  spiSendOctet(CMD_WRITE);
  spiSendOctet(HIGHSCORE_ADDR);
  spiSendOctet(buf.buffer[0]);
  spiSendOctet(buf.buffer[1]);
  spiSendOctet(buf.buffer[2]);
  spiSendOctet(buf.buffer[3]);
  spiSendEnd(e_SPI_EEPROM);
}

static void readBuf() {
  spiSendBegin(e_SPI_EEPROM);
  spiSendOctet(CMD_READ);
  spiReceiveOctet();
  spiSendOctet(HIGHSCORE_ADDR);
  spiReceiveOctet();
  spiSendOctet(DUMMY);
  buf.buffer[0] = spiReceiveOctet();
  spiSendOctet(DUMMY);
  buf.buffer[1] = spiReceiveOctet();
  spiSendOctet(DUMMY);
  buf.buffer[2] = spiReceiveOctet();
  spiSendOctet(DUMMY);
  buf.buffer[3] = spiReceiveOctet();
  spiSendEnd(e_SPI_EEPROM);
}

void eepromInit() {
  readBuf();

  if (buf.v.magic != MAGIC) {
    buf.v.magic = MAGIC;
    buf.v.highScore = 0;
    writeBuf();
  }
}

uint16_t eepromReadHighScore() {
  return buf.v.highScore;
}

void eepromWriteHighScore(uint16_t v) {
  buf.v.highScore = v;
  writeBuf();
}

