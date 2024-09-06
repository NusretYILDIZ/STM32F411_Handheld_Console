#ifndef __timer_h
#define __timer_h

#include <stdint.h>

#define FRAME_TIME  33

extern uint32_t elapsed_time;
extern uint32_t delta_time;

void wait_frame_time(void);
void system_sleep(uint32_t time);
uint32_t get_tick(void);

#endif //__timer_h