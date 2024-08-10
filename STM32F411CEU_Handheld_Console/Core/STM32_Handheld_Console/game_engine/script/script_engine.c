#include "./script_engine.h"
#include "./instructions.h"
#include "./syscalls.h"
#include "./mem_access_def.h"
#include <string.h>

// TODO: Implement flags properly using bitwise.
PANIC_CODE panic_code = PANIC_NONE;

uint8_t ram[RAM_SIZE] = { 0 };
//uint32_t stack[STACK_SIZE] = { 0 };

RAM_PTR prg_counter = 0;
STACK_PTR stack_ptr = 0;

//uint32_t a_int = 0;
//float a_flt = 0;
uint8_t status_flag = 0;
uint8_t end_of_loop_flag = 0;  // TODO: Store every flag in a single variable.
//ram_t abs_addr = 0;
//ram_t ptr_addr = 0;

void vm_init()
{
	memset(ram, 0, sizeof(ram));
	prg_counter = 0;
	stack_ptr = 0;
}

// Switch-case is faster than function table on embedded systems.
// https://stackoverflow.com/a/35846099

#define INST_SWITCHCASE(ins)  case enum_inst_##ins: prg_counter++; vm_inst_##ins(); break;
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
#undef INST_SWITCHCASE

void vm_push(uint32_t data)
{
    write_uint32(data, stack_ptr * sizeof(uint32_t));
    ++stack_ptr;
}

uint32_t vm_pop(void)
{
    --stack_ptr;
    return ram_ptr_uint32(stack_ptr * sizeof(uint32_t));
}

