#ifndef __stm32f411_input_h
#define __stm32f411_input_h

#include <stm32f4xx_hal.h>

extern uint32_t gpioa_moder, input_en_pupdr;

#define enable_input()        GPIOB->MODER  = 0x00000000  // Set Port B as input

#define disable_input()       GPIOB->MODER  = 0x55555555  // Set Port B as output

//#define enable_input()        /* Set Port B as input */            GPIOB->MODER  = 0x00000000; \
                              /* Save Port A's normal mode */      gpioa_moder   = GPIOA->MODER; \
                              /* Set input enable pin as output */ GPIOA->MODER |= 0x04000000; \
                              /* Set input enable pin as high */   GPIOA->BSRR   = GPIO_PIN_13

//#define disable_input()       /* Set input enable pin as low */    GPIOA->BSRR   = GPIO_PIN_13 << 16; \
                              /* Set input enable pin as input */  GPIOA->MODER  = gpioa_moder; \
                              /* Set Port B as output */           GPIOB->MODER  = 0x55555555

#define get_input_status()    ((uint16_t)(GPIOB->IDR))

#endif //__stm32f411_input_h
