/*
 * PontCoopScheduler.c
 *
 *  Created on: 29.08.2016
 *      Author: wn
 */


#include <stdlib.h>


#include "PontCoopScheduler.h"

tTask tasks[MAX_NUM_OF_TASKS];


void schInit() {
  for (uint8_t i = 0; i < MAX_NUM_OF_TASKS; i++) {
    tasks[i].delay = 0;
    tasks[i].period = 0;
    tasks[i].run = 0;
    tasks[i].exec = NULL;
    tasks[i].handle = NULL;
  }
}

void schAdd(void (*exec)(void *), void *handle, uint32_t delay, uint32_t period) {
  for (uint8_t i = 0; i < MAX_NUM_OF_TASKS; i++) {
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

void schDel(void (*exec)(void *), void *handle) {
  for (uint8_t i = 0; i < MAX_NUM_OF_TASKS; i++) {
    if ((tasks[i].exec == exec) && (tasks[i].handle == handle)) {
      tasks[i].exec = NULL;
      break;
    }
  }
}

void schExec() {
  for (uint8_t i = 0; i < MAX_NUM_OF_TASKS; i++) {
    if (tasks[i].exec != NULL && tasks[i].run > 0) {
      tasks[i].run--;
      tasks[i].exec(tasks[i].handle);
      if (tasks[i].period == 0) {
        tasks[i].exec = NULL;
      }
    }
  }
}



void schUpdate() {
  for (uint8_t i = 0; i < MAX_NUM_OF_TASKS; i++) {
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

uint8_t schTaskCnt() {
  uint8_t cnt = 0;
  for (uint8_t i = 0; i < MAX_NUM_OF_TASKS; i++) {
    if (tasks[i].exec != NULL){
      cnt++;
    } 
  }
  return cnt;
}