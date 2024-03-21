#include <string.h>
#include <stdint.h>

#include <msp430g2553.h>

#include "canvas.h"


static uint8_t canvasStorage[CANVAS_WIDTH * CANVAS_HEIGHT];
const canvas_t canvas = { 
  .height = CANVAS_HEIGHT,
  .width = CANVAS_WIDTH,
  .canvas = canvasStorage
};


inline static void spiSendOctet(uint8_t v) {
  // wait for TX buffer empty
  while (!(UC0IFG & UCB0TXIFG));
  // load octet into TX buffer
  UCB0TXBUF = v;
}

void canvasShow() {
  // wait for signal waiting for data
  while (!(P1IN & BIT3));

  for (uint8_t i = 0; i < (CANVAS_WIDTH*CANVAS_HEIGHT); i++) {
    if ((*((canvas.canvas)+i) & 0x80) != 0) {
      *((canvas.canvas)+i) &= ~0x80;
      spiSendOctet(i);
      spiSendOctet(*((canvas.canvas)+i));
    }
  }
  spiSendOctet(0xfe);
}

void canvasInit() {
  // SPI in master mode
  UCB0CTL0 = UCMST;
  // SPI timing config
  UCB0CTL1 = UCSSEL_3;
  // Faster than 8 ends up in strange communication errors
  // between the both MCUs.
  // With 8 the transfer of a complete 110 pixel canvas takes
  // about 720us.
  // 8 was still too fast and caused problems.
  UCB0BR0 = 16; 
  UCB0BR1 = 0;

  // BIT5: UCB0CLK
  // BIT6: UCB0SOMI
  // BIT7: UCB0SIMO
  P1SEL |= BIT5 | BIT6 | BIT7;
  P1SEL2 |= BIT5 | BIT6 | BIT7;
  P1DIR |= BIT5 | BIT7;

  // P1.3 is signal line
  P1DIR &= ~BIT3;

  // enable SPI module
  UCB0CTL1 &= ~UCSWRST;


  canvasClear();
  canvasShow();
}

void canvasClear() {
  memset(canvas.canvas, 0x80, CANVAS_WIDTH*CANVAS_HEIGHT);
}

void canvasSetAll(uint8_t color) {
  memset(canvas.canvas, color + 0x80, CANVAS_WIDTH*CANVAS_HEIGHT);
}

void canvasSetPixel(uint8_t column, uint8_t row, uint8_t color) {
  *((canvas.canvas) + (row * canvas.width + column)) = (color + 0x80);
}

void canvasWipeRow(uint8_t row) {
  memmove(((canvas.canvas)+canvas.width), canvas.canvas, canvas.width*row);
  for (uint8_t i = 10; i < canvas.width*(row+1); i++) {
    *((canvas.canvas)+i) += 0x80;
  }
  memset(canvas.canvas, 0x80, canvas.width);
}

uint8_t canvasIsRowFilled(uint8_t row) {
  uint8_t res = 1;
  for (uint8_t column = 0; column < canvas.width; column++) {
    if (*((canvas.canvas) + (row * canvas.width + column)) == 0) {
      res = 0;
      break;
    }
  }
  return res;
}

uint8_t canvasIsPixelFree(uint8_t column, uint8_t row) {
  return (*((canvas.canvas) + (row * canvas.width + column)) == 0) &&
         (column < canvas.width) &&
         (row < canvas.height);
}

