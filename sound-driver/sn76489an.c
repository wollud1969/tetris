#include <msp430g2553.h>
#include <stdint.h>
#include <stdlib.h>

#include "psg.h"
#include "scheduler.h"


// generated using utils/calc-76489an.py
const uint16_t frequencyCodes[8][12] = {
  { 3420, 3229, 3047, 2876, 2715, 2562, 2419, 2283, 2155, 2034, 1920, 1812 }, 
  { 1710, 1614, 1524, 1438, 1357, 1281, 1209, 1141, 1077, 1017, 960, 906 }, 
  { 855, 807, 762, 719, 679, 641, 605, 571, 539, 508, 480, 453 }, 
  { 428, 404, 381, 360, 339, 320, 302, 285, 269, 254, 240, 226 }, 
  { 214, 202, 190, 180, 170, 160, 151, 143, 135, 127, 120, 113 }, 
  { 107, 101, 95, 90, 85, 80, 76, 71, 67, 64, 60, 57 }, 
  { 53, 50, 48, 45, 42, 40, 38, 36, 34, 32, 30, 28 }, 
  { 27, 25, 24, 22, 21, 20, 19, 18, 17, 16, 15, 14 }
};


#define ADDR_DATA_REG P2OUT
#define BUS_CTRL_REG P1OUT
#define BUS_CTRL_IN_REG P1IN
#define _CS0 BIT0
#define _CS1 BIT1
#define _WE BIT2
#define READY BIT3

#define CHANNEL_A_PERIOD_ADDR 0
#define CHANNEL_A_ATTEN_ADDR 1
#define CHANNEL_B_PERIOD_ADDR 2
#define CHANNEL_B_ATTEN_ADDR 3
#define CHANNEL_C_PERIOD_ADDR 4
#define CHANNEL_C_ATTEN_ADDR 5

#define IGNORE_OCTET 0xff

uint8_t psgAmplitudeShadowValue[3];

static void delay() {
  asm volatile (
      "push r12\n"
      "mov.w #5, r12\n"
      "loop:\n"
      "dec.w r12\n"
      "jnz loop\n"
      "pop r12\n"
  );
}

inline static void WRITE_CYCLE(uint8_t chipNo) {
  if (chipNo == 0) {
    BUS_CTRL_REG &= ~_CS0;
  } else {
    BUS_CTRL_REG &= ~_CS1;
  }

  BUS_CTRL_REG &= ~_WE;

  delay();

  while ((BUS_CTRL_IN_REG & READY) == 0);

  BUS_CTRL_REG |= _WE;

  if (chipNo == 0) {
    BUS_CTRL_REG |= _CS0;
  } else {
    BUS_CTRL_REG |= _CS1;
  }

  delay();
}

static void psgWrite(uint8_t chipNo, uint8_t value) {
  ADDR_DATA_REG = value;
  WRITE_CYCLE(chipNo);
}

static void psgWriteFrequency(uint8_t channel, uint16_t frequencyCode) {
  uint8_t chipNo = channel / 3;
  uint8_t regAddr = (channel % 3) * 2;

  // bit order in frequncyCode and order in octet on data bus are reversed
  // see datacheat cp. 1 and cp. 6
  uint8_t firstOctet = 0x01;
  firstOctet |= ((regAddr & 0x04) > 1);
  firstOctet |= ((regAddr & 0x02) < 1);
  firstOctet |= ((regAddr & 0x01) < 3);
  uint8_t lowerPart = frequencyCode & 0x0f;
  firstOctet |= ((lowerPart & 0x08) << 1);
  firstOctet |= ((lowerPart & 0x04) << 3);
  firstOctet |= ((lowerPart & 0x02) << 5);
  firstOctet |= ((lowerPart & 0x01) << 7);

  uint8_t secondOctet = 0;
  uint8_t upperPart = (frequencyCode & 0x03f0) >> 4;
  secondOctet |= ((upperPart & 0x20) >> 3);
  secondOctet |= ((upperPart & 0x10) >> 1);
  secondOctet |= ((upperPart & 0x08) << 1);
  secondOctet |= ((upperPart & 0x04) << 3);
  secondOctet |= ((upperPart & 0x02) << 5);
  secondOctet |= ((upperPart & 0x01) << 7);

  ADDR_DATA_REG = firstOctet;
  WRITE_CYCLE(chipNo);

  ADDR_DATA_REG = secondOctet;
  WRITE_CYCLE(chipNo);
}

void psgAmplitude(uint8_t channel, uint8_t volume) {
  psgAmplitudeShadowValue[channel] = volume;
  uint8_t chipNo = channel / 3;
  uint8_t regAddr = ((channel % 3) * 2) + 1;

  uint8_t attenuation = 15 - volume;

  uint8_t firstOctet = 0x01;
  firstOctet |= ((regAddr & 0x04) >> 1);
  firstOctet |= ((regAddr & 0x02) << 1);
  firstOctet |= ((regAddr & 0x01) << 3);
  firstOctet |= ((attenuation & 0x01) << 7);
  firstOctet |= ((attenuation & 0x02) << 5);
  firstOctet |= ((attenuation & 0x04) << 3);
  firstOctet |= ((attenuation & 0x08) << 1);

  ADDR_DATA_REG = firstOctet;
  WRITE_CYCLE(chipNo);
}

void psgPlayTone(uint8_t channel, uint8_t volume, t_octave octave, t_note note) {
  if (note == e_Pause) {
    psgAmplitude(channel, 0);
  } else {
//    if (psgAmplitudeShadowValue[channel] == 0) {
      psgAmplitude(channel, volume);
//    }
    psgWriteFrequency(channel, frequencyCodes[octave][note]);
  }
}

void psgInit() {
  // address/data bus
  P2DIR = 0xff;
  P2SEL = 0;
  P2SEL2 = 0;

  // bus control lines
  //   output:
  //     BIT0: /CS chip 0
  //     BIT1: /CS chip 1
  //     BIT2: /WE
  //   input:
  //     BIT3: READY
  P1DIR |= BIT0 | BIT1 | BIT2;
  P1DIR &= ~BIT3;
  // immediately disable all outputs, all are active low
  P1OUT |= BIT0 | BIT1 | BIT2;

  // shutdown all channels including noise
  psgWrite(0, 0b11111001);
  psgWrite(0, 0b11111101);
  psgWrite(0, 0b11111011);
  psgWrite(0, 0b11111111);

//  psgPlayTone(0, 5, e_O_3, e_A);
  psgAmplitude(0, 3);
}

