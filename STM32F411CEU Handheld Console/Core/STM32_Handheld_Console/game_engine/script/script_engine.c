#include "./script_engine.h"
#include "./instructions.h"
#include "./syscalls.h"

uint8_t ram[RAM_SIZE] = { 0 };
uint32_t stack[STACK_SIZE] = { 0 };

ram_t prg_counter = 0;
stack_t stack_ptr = 0;

//uint32_t a_int = 0;
//float a_flt = 0;
uint8_t logical_flag = 0;
//ram_t abs_addr = 0;
//ram_t ptr_addr = 0;

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

void vm_push(uint32_t data)
{
    stack[stack_ptr] = data;
    ++stack_ptr;
}

uint32_t vm_pop(void)
{
    --stack_ptr;
    return stack[stack_ptr];
}

