/*
 * PontCoopScheduler.h
 *
 *  Created on: 29.08.2016
 *      Author: wn
 */

#ifndef PONTCOOPSCHEDULER_H_
#define PONTCOOPSCHEDULER_H_


#include <stdint.h>



#define MAX_NUM_OF_TASKS 2


typedef struct {
  uint16_t delay;
  uint16_t period;
  uint8_t run;
  void (*exec)(void *handle);
  void *handle;
} tTask;


void schInit();
void schAdd(void (*exec)(void *), void *handle, uint32_t delay, uint32_t period);
void schDel(void (*exec)(void *), void *handle);
void schExec();
void schUpdate();
uint8_t schTaskCnt();


#endif /* PONTCOOPSCHEDULER_H_ */
