#include <stdlib.h>
#include <msp430g2553.h>
#include "scheduler.h"

tTask tasks[MAX_NUM_OF_TASKS];


void schInit() {
  P1DIR |= BIT0;
  TACCR0 = 19600;
  TACCTL0 = CCIE;
  TACTL = MC_1 | ID_0 | TASSEL_2 | TACLR;

  for (uint16_t i = 0; i < MAX_NUM_OF_TASKS; i++) {
    tasks[i].delay = 0;
    tasks[i].period = 0;
    tasks[i].run = 0;
    tasks[i].exec = NULL;
    tasks[i].handle = NULL;
  }
}

void __attribute__ ((interrupt (TIMER0_A0_VECTOR))) schUpdate() {
  P1OUT ^= BIT0;
  for (uint16_t i = 0; i < MAX_NUM_OF_TASKS; i++) {
    if (tasks[i].exec != NULL) {
      if (tasks[i].delay == 0) {
        tasks[i].delay = tasks[i].period;
        tasks[i].run++;
      } else {
        tasks[i].delay--;
      }
    }
  }
}

void schAdd(void (*exec)(void *), void *handle, uint32_t delay, uint32_t period) {
  for (uint16_t i = 0; i < MAX_NUM_OF_TASKS; i++) {
    if (tasks[i].exec == NULL) {
      tasks[i].delay = delay;
      tasks[i].period = period;
      if (delay == 0 && period == 0) {
        tasks[i].run = 1;
      } else {
        tasks[i].run = 0;
      }
      tasks[i].exec = exec;
      tasks[i].handle = handle;
      break;
    }
  }
}

/*
void schDel(void (*exec)(void *), void *handle) {
  for (uint16_t i = 0; i < MAX_NUM_OF_TASKS; i++) {
    if ((tasks[i].exec == exec) && (tasks[i].handle == handle)) {
      tasks[i].exec = NULL;
      break;
    }
  }
}
*/

void schExec() {
  for (uint16_t i = 0; i < MAX_NUM_OF_TASKS; i++) {
    // synchronize access to tasks[].run
    __disable_interrupt(); 
    if (tasks[i].exec != NULL && tasks[i].run > 0) {
      tasks[i].run--;
      // synchronize access to tasks[].run
      // reenable interrupts before actually executing task
      __enable_interrupt();
      tasks[i].exec(tasks[i].handle);
      if (tasks[i].period == 0) {
        tasks[i].exec = NULL;
      }
    } else {
      // synchronize access to tasks[].run
      // reenable interrupts in case task is not yet executable
      __enable_interrupt();
    }
  }
}

