#ifndef PONTCOOPSCHEDULER_H_
#define PONTCOOPSCHEDULER_H_


#include <stdint.h>



#define MAX_NUM_OF_TASKS 4


typedef struct {
  uint16_t delay;
  uint16_t period;
  uint8_t run;
  void (*exec)(void *handle);
  void *handle;
} tTask;


void schInit();
uint16_t schAdd(void (*exec)(void *), void *handle, uint32_t delay, uint32_t period);
// void schDel(void (*exec)(void *), void *handle);
void schDel(uint16_t taskId);
void schExec();


#endif /* PONTCOOPSCHEDULER_H_ */
