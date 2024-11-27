/*
	MIT License

	Copyright (c) 2024 Nusret YILDIZ

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/

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

#define get_input_status()    (GPIOB->IDR)

#endif //__stm32f411_input_h
