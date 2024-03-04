#ifndef __timer_h
#define __timer_h

#include <stdint.h>

void system_sleep(uint32_t time);
uint32_t get_tick(void);

#endif //__timer_h