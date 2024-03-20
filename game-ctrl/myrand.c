#include <stdint.h>
#include <msp430g2553.h>

#include "myrand.h"

void myRandInit() {
  ADC10CTL0 = SREF_1 | ADC10SHT_1 | ADC10SR | REFON | ADC10ON;
  ADC10CTL1 = INCH_10;
}

uint8_t myRandGet() {
  ADC10CTL0 |= ENC | ADC10SC;

  while ((ADC10CTL0 & ADC10IFG) == 0);
  
  uint16_t n = ADC10MEM;
  uint8_t r = n & 0x00ff;

  ADC10CTL0 &= ~(ADC10IFG | ENC);

  return r;
}

  
