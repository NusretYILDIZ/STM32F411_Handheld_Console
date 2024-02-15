#include "./script_engine.h"

uint8_t ram[RAM_SIZE] = { 0 };
uint32_t stack[STACK_SIZE] = { 0 };

ram_t prg_counter = 0;
stack_t stack_ptr = 0;

uint32_t a_int = 0;
float a_flt = 0;
uint8_t logical_flag = 0;
ram_t abs_addr = 0;
ram_t ptr_addr = 0;

// Switch-case is faster than function table on embedded systems.
// https://stackoverflow.com/a/35846099

#define INST_SWITCHCASE(opc, ins)  case opc: vm_inst_##ins(); break;
void vm_execute()
{
	switch(ram[prg_counter])
	{
		INST_TABLE(INST_SWITCHCASE)
	}
}
#undef INST_SWITCHCASE

__attribute__((always_inline)) void vm_inst_syscall()
{
	
}

__attribute__((always_inline)) void vm_inst_assign()
{
	// TODO: Add attribute byte support.
	++prg_counter;
	abs_addr = *(ram_t *)(&ram[prg_counter]);
	prg_counter += sizeof(ram_t);
	a_int = *(uint32_t *)(&ram[prg_counter]);
	prg_counter += sizeof(uint32_t);
	*(uint32_t *)(&ram[abs_addr]) = a_int;
}

__attribute__((always_inline)) void vm_inst_arith_calc()
{
	
}

__attribute__((always_inline)) void vm_inst_bitwise()
{
	
}

__attribute__((always_inline)) void vm_inst_logical()
{
	
}

__attribute__((always_inline)) void vm_inst_jsr()
{
	
}

__attribute__((always_inline)) void vm_inst_rts()
{
	
}

__attribute__((always_inline)) void vm_inst_jump_if()
{
	
}

__attribute__((always_inline)) void vm_inst_jump()
{
	
}

__attribute__((always_inline)) void vm_inst_exit()
{
	
}