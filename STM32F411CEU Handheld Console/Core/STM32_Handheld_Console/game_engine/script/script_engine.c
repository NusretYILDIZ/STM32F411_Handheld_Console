#include "./script_engine.h"

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

__attribute__((always_inline)) void vm_inst_syscall()
{
	
}

__attribute__((always_inline)) void vm_inst_assign()
{
	++prg_counter;  // Get to the operand attribute byte location
	
	uint8_t addr_mode = ram[prg_counter] & ADDR_MASK;
	uint8_t dest_data_type = ram[prg_counter] & TYPE_MASK;
	
	++prg_counter;  // Get to the destination address location
	
	ram_t dest_addr = *(ram_t *) (&ram[prg_counter]);
	
	if(addr_mode == ADDR_PTR)
		dest_addr = *(ram_t *) (&ram[dest_addr]);
	
	prg_counter += sizeof(ram_t);  // Get to the operand attribute byte location
	
	addr_mode = ram[prg_counter] & ADDR_MASK;
	uint8_t src_data_type = ram[prg_counter] & TYPE_MASK;
	ram_t src_addr;
	uint32_t tmp;
	
	++prg_counter;  // Get to the data to assign location
	
	if(addr_mode == ADDR_IMM) 
	{
		src_addr = prg_counter;
		
		prg_counter += (src_data_type == TYPE_FLOAT || src_data_type == TYPE_INT32 || src_data_type == TYPE_UINT32) ? sizeof(uint32_t) :
		               (src_data_type == TYPE_INT16 || src_data_type == TYPE_UINT16) ? sizeof(uint16_t) :
					   sizeof(uint8_t);
	}
	else
	{
		src_addr = *(ram_t *)(&ram[prg_counter]);
		
		if(addr_mode == ADDR_PTR)
			src_addr = *(ram_t *)(&ram[src_addr]);
		
		prg_counter += sizeof(ram_t);
	}
	
	if(src_data_type == TYPE_FLOAT || src_data_type == TYPE_INT32 || src_data_type == TYPE_UINT32)
		tmp = *(uint32_t *) (&ram[src_addr]);
	
	else if(src_data_type == TYPE_INT16 || src_data_type == TYPE_UINT16)
		tmp = (uint32_t) *(uint16_t *) (&ram[src_addr]);
	
	else if(src_data_type == TYPE_INT8 || src_data_type == TYPE_UINT8)
		tmp = (uint32_t) *(uint8_t *) (&ram[src_addr]);
	
	else return;  // Illegal attribute, terminate the instruction
	
	
	if(dest_data_type == TYPE_FLOAT || src_data_type == TYPE_INT32 || src_data_type == TYPE_UINT32)
		*(uint32_t *) (&ram[dest_addr]) = tmp;
	
	else if(src_data_type == TYPE_INT16 || src_data_type == TYPE_UINT16)
		*(uint16_t *) (&ram[dest_addr]) = (uint16_t) tmp;
	
	else if(src_data_type == TYPE_INT8 || src_data_type == TYPE_UINT8)
		ram[dest_addr] = (uint8_t) tmp;
}

__attribute__((always_inline)) void vm_inst_arith_calc()
{
	++prg_counter;
	
	uint8_t addr_mode = ram[prg_counter] & ADDR_MASK;
	uint8_t data_type = ram[prg_counter] & TYPE_MASK;
	
	++prg_counter;
	
	ram_t dest_addr = *(ram_t *) (&ram[prg_counter]);
	if(addr_mode == ADDR_PTR)
		dest_addr = *(ram_t *) (&ram[dest_addr]);
	
	prg_counter += sizeof(ram_t);
	
	uint32_t tmp_int;
	float tmp_flt;
	uint8_t float_flag = 0;
	
	for(;;)
	{
		uint8_t operand_addr_mode = ram[prg_counter] & ADDR_MASK;
		uint8_t operand_data_type = ram[prg_counter] & TYPE_MASK;
		ram_t operand_addr;
		uint8_t operand_operation = ram[prg_counter] & OPER_MASK;
		
		if(operand_data_type == TYPE_TERMINATE) break;
		
		if(operand_addr_mode == ADDR_IMM)
		{
			operand_addr = prg_counter;
		
			prg_counter += (operand_data_type == TYPE_FLOAT || operand_data_type == TYPE_INT32 || operand_data_type == TYPE_UINT32) ? sizeof(uint32_t) :
						   (operand_data_type == TYPE_INT16 || operand_data_type == TYPE_UINT16) ? sizeof(uint16_t) :
						   sizeof(uint8_t);
		}
		else
		{
			operand_addr = *(ram_t *)(&ram[prg_counter]);
		
			if(operand_addr_mode == ADDR_PTR)
				operand_addr = *(ram_t *)(&ram[operand_addr]);
			
			prg_counter += sizeof(ram_t);
		}
		
		if(operand_operation == ARITH_NOP)  // Should be used only for the first operand
		{
			
		}
	}
}

__attribute__((always_inline)) void vm_inst_bitwise()
{
	
}

__attribute__((always_inline)) void vm_inst_logical()
{
	
}

__attribute__((always_inline)) void vm_inst_jsr()
{
	++prg_counter;
	
	ram_t jmp_addr = *(ram_t *) (&ram[prg_counter]);
	prg_counter += sizeof(ram_t);
	
	vm_push(prg_counter);
	prg_counter = jmp_addr;
}

__attribute__((always_inline)) void vm_inst_rts()
{
	prg_counter = (ram_t) vm_pop();
}

__attribute__((always_inline)) void vm_inst_jump_if()
{
	++prg_counter;
	(logical_flag) ? prg_counter = *(ram_t *) (&ram[prg_counter]) : prg_counter += sizeof(ram_t);
}

__attribute__((always_inline)) void vm_inst_jump()
{
	++prg_counter;
	prg_counter = *(ram_t *) (&ram[prg_counter]);
}

__attribute__((always_inline)) void vm_inst_exit()
{
	
}