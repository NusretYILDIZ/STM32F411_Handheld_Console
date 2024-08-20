#include "./script_engine.h"
#include "./instructions.h"
#include "./syscalls.h"
#include <string.h>

PANIC_CODE panic_code = PANIC_NONE;

uint8_t ram[RAM_SIZE];
RPN_STACK_DATA rpn_stack[RPN_STACK_SIZE];
uint32_t *stack = ram;  // The stack is always at the start of ram.

RAM_PTR prg_counter = 0;
STACK_PTR stack_ptr = 0;
uint8_t rpn_stack_ptr = 0;

uint8_t status_flag = 0;

void vm_init()
{
	memset(ram, 0, sizeof(ram));
	memset(rpn_stack, 0, sizeof(rpn_stack));
	prg_counter = 0;
	stack_ptr = 0;
	rpn_stack_ptr = 0;
	status_flag = 0;
	panic_code = PANIC_NONE;
}

// Switch-case is faster than function table on embedded systems.
// https://stackoverflow.com/a/35846099

#define INST_SWITCHCASE(ins)  case enum_inst_##ins: prg_counter++; vm_inst_##ins(); break;
//#define INST_SWITCHCASE(ins)  case enum_inst_##ins: prg_counter++; show_info_window("", #ins); vm_inst_##ins(); break;
//#define INST_SWITCHCASE(ins)  case enum_inst_##ins: printf("%s\n", #ins); prg_counter++; vm_inst_##ins(); break;
void vm_execute()    // Executes a single instruction.
{
    switch(ram[prg_counter])
    {
       INST_TABLE(INST_SWITCHCASE)
    }
}

void vm_run()  // Continuously executes instructions until reaches "end_of_loop" instruction. Requires manually resetting end of loop flag.
{
	while(!((status_flag & END_OF_LOOP_FLAG) || (status_flag & KERNEL_PANIC_FLAG)))
	{
		switch(ram[prg_counter])
		{
		default:
			KERNEL_PANIC(PANIC_INVALID_INSTRUCTION);
			break;
			
		INST_TABLE(INST_SWITCHCASE)
		}
	}
}

void vm_push_stack(uint32_t data)
{
	if(stack_ptr >= STACK_SIZE)
	{
		KERNEL_PANIC(PANIC_STACK_OVERFLOW);
		return;
	}
	
	stack[stack_ptr] = data;
    ++stack_ptr;
}

uint32_t vm_pop_stack(void)
{
	if(stack_ptr == 0)
	{
		KERNEL_PANIC(PANIC_STACK_UNDERFLOW);
		return (uint32_t)(-1);
	}
	
    --stack_ptr;
    return stack[stack_ptr];
}

