#ifndef __stm32f411_input_h
#define __stm32f411_input_h

#include <stm32f4xx_hal.h>

#define get_gpiob_status()    (uint16_t)(GPIOB->IDR)

#endif //__stm32f411_input_h