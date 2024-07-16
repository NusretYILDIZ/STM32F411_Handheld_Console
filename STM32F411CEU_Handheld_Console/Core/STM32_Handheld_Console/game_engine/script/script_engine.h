#ifndef __script_engine_h
#define __script_engine_h

#include <stdint.h>
#include "../../display/display_driver.h"

#define RAM_SIZE    (1024 * 80) // 85 KB (Max possible size is 88 KB but expect it to be lesser than that.)
#define STACK_SIZE  (256)

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;

#if (RAM_SIZE > 65536)
	typedef uint32_t RAM_PTR;
#else
	typedef uint16_t RAM_PTR;
#endif

#if (STACK_SIZE > 256)
	typedef uint16_t STACK_PTR;
#else
	typedef uint8_t STACK_PTR;
#endif

extern uint8_t ram[RAM_SIZE];
//extern uint32_t stack[STACK_SIZE];

extern RAM_PTR prg_counter;
extern STACK_PTR stack_ptr;

//extern uint32_t a_int;
//extern float a_flt;
extern uint8_t logical_flag;
extern uint8_t end_of_loop_flag;
//extern ram_t abs_addr;
//extern ram_t ptr_addr;

void vm_init(void);
void vm_execute(void);
void vm_run(void);
void vm_push(uint32_t data);
uint32_t vm_pop(void);

#endif //__script_engine_h