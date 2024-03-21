#include <stdint.h>
#include <msp430g2553.h>

#include "myrand.h"

void myRandInit() {
  ADC10CTL1 = INCH_10;
  ADC10CTL0 = SREF_1 | ADC10SHT_1 | REFON | ADC10ON;
}

uint16_t myRandGet() {
  uint16_t res = 0;

  for (uint8_t i = 0; i < 16; i++) {
    ADC10CTL0 |= ENC | ADC10SC;

    while ((ADC10CTL1 & ADC10BUSY));
  
    res <<= 1;
    res |= ADC10MEM & 0x0001;
  }

  return res;
}

  
