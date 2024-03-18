#include <msp430g2553.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include "time.h"
#include "scheduler.h"
#include "led.h"
#include "canvas.h"
#include "game.h"
#include "buttons.h"
#include "shapes.h"


int main() {
    WDTCTL = WDTPW | WDTHOLD;

    __disable_interrupt();

    // highest possible system clock
    DCOCTL = DCO0 | DCO1 | DCO2;
    BCSCTL1 = XT2OFF | RSEL0 | RSEL1 | RSEL2 | RSEL3;
    BCSCTL2 = 0;
    BCSCTL3 = 0;

    schInit();

    ledInit();
    canvasInit();

    shapesInit();
    gameInit();
    buttonsInit();

    __enable_interrupt();

    while (1) {
        schExec();
    }
}
