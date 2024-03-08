#include <msp430g2553.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include "time.h"
#include "PontCoopScheduler.h"
#include "led.h"
#include "displayDriver.h"
#include "canvas.h"
#include "displayTest.h"


int main() {
    WDTCTL = WDTPW | WDTHOLD;

    __disable_interrupt();

    // highest possible system clock
    DCOCTL = DCO0 | DCO1 | DCO2;
    BCSCTL1 = XT2OFF | RSEL0 | RSEL1 | RSEL2 | RSEL3;
    BCSCTL2 = 0;
    BCSCTL3 = 0;


    timeInit();
    schInit();

    ledInit();
    displayDriverInit();
    canvasInit();
    displayTestInit();


    __enable_interrupt();

    while (1) {
        schExec();
    }
}
