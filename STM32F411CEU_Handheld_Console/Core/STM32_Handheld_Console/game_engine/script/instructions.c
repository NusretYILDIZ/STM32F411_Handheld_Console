#include "./instructions.h"
#include "./script_engine.h"
#include "./mem_access_def.h"
#include <math.h>

#define _INLINE_  __attribute__((always_inline)) inline 

_INLINE_ void vm_inst_syscall()
{
    
}

_INLINE_ void vm_inst_assign()
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

_INLINE_ void vm_inst_arith_calc()
{
    ++prg_counter;
    
    uint8_t dest_addr_mode = ram[prg_counter] & ADDR_MASK;
    uint8_t dest_data_type = ram[prg_counter] & TYPE_MASK;
    
    ++prg_counter;
    
    ram_t dest_addr = *(ram_t *) (&ram[prg_counter]);
    if(dest_addr_mode == ADDR_PTR)
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
        
        ++prg_counter;
        
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
        
        uint32_t operand_data;
        
        if(operand_data_type == TYPE_FLOAT || operand_data_type == TYPE_INT32 || operand_data_type == TYPE_UINT32)
            operand_data = *(uint32_t *) (&ram[operand_addr]);
        
        else if(operand_data_type == TYPE_INT16 || operand_data_type == TYPE_UINT16)
            operand_data = (uint32_t) *(uint16_t *) (&ram[operand_addr]);
        
        else //if(operand_data_type == TYPE_INT8 || operand_data_type == TYPE_UINT8)
            operand_data = (uint32_t) ram[operand_addr];
        
        if(operand_data_type == TYPE_FLOAT && !float_flag)
        {
            tmp_flt = (float) tmp_int;
            float_flag = 1;
        }
        
        switch(operand_operation)
        {
        case ARITH_NOP:
            if(float_flag)
                tmp_flt = *(float *) (&operand_data);
            else
                tmp_int = operand_data;
            break;
        
        case ARITH_ADD:
            if(float_flag)
                tmp_flt += *(float *) (&operand_data);
            else
                tmp_int += operand_data;
            break;
        
        case ARITH_SUB:
            if(float_flag)
                tmp_flt -= *(float *) (&operand_data);
            else
                tmp_int -= operand_data;
            break;
        
        case ARITH_MUL:
            if(float_flag)
                tmp_flt *= *(float *) (&operand_data);
            else
                tmp_int *= operand_data;
            break;
        
        case ARITH_DIV:
            if(float_flag)
                tmp_flt /= *(float *) (&operand_data);
            else
                tmp_int /= operand_data;
            break;
        
        case ARITH_MOD:
            if(float_flag)
            {
                tmp_int = ((uint32_t) tmp_flt) % operand_data;
                float_flag = 0;
            }
            else
                tmp_int %= operand_data;
            break;
        
        case ARITH_POW:
            if(float_flag)
                tmp_flt = powf(tmp_flt, *(float *) (&operand_data));
            else
                tmp_int = (uint32_t) powf((float) tmp_int, (float) operand_data);
            break;
        }
    }
    
    if(dest_data_type == TYPE_FLOAT)
    {
        if(float_flag)
            *(float *) (&ram[dest_addr]) = tmp_flt;
        else
            *(float *) (&ram[dest_addr]) = (float) tmp_int;
    }
    else if(dest_data_type == TYPE_INT32 || dest_data_type == TYPE_UINT32)
    {
        if(float_flag)
            *(uint32_t *) (&ram[dest_addr]) = (uint32_t) tmp_flt;
        else
            *(uint32_t *) (&ram[dest_addr]) = tmp_int;
    }
    else if(dest_data_type == TYPE_INT16 || dest_data_type == TYPE_UINT16)
    {
        if(float_flag)
            *(uint16_t *) (&ram[dest_addr]) = (uint16_t) tmp_flt;
        else
            *(uint16_t *) (&ram[dest_addr]) = tmp_int & 0xffff;
    }
    else //if(dest_data_type == TYPE_INT8 || dest_data_type == TYPE_UINT8)
    {
        if(float_flag)
            ram[dest_addr] = (uint8_t) tmp_flt;
        else
            ram[dest_addr] = tmp_int & 0xff;
    }
}

_INLINE_ void vm_inst_bitwise()
{
    
}

_INLINE_ void vm_inst_logical()
{
    
}

_INLINE_ void vm_inst_jsr()
{
    ++prg_counter;
    
    ram_t jmp_addr = *(ram_t *) (&ram[prg_counter]);
    prg_counter += sizeof(ram_t);
    
    vm_push(prg_counter);
    prg_counter = jmp_addr;
}

_INLINE_ void vm_inst_rts()
{
    prg_counter = (ram_t) vm_pop();
}

_INLINE_ void vm_inst_jump_if()
{
    ++prg_counter;
    
    if(logical_flag)
        prg_counter = *(ram_t *) (&ram[prg_counter]);
    else
        prg_counter += sizeof(ram_t);
}

_INLINE_ void vm_inst_jump()
{
    ++prg_counter;
    prg_counter = *(ram_t *) (&ram[prg_counter]);
}

_INLINE_ void vm_inst_exit()
{
    
}

_INLINE_ void vm_inst_set_text_area()
{
    
}

_INLINE_ void vm_inst_set_cursor()
{
    
}

_INLINE_ void vm_inst_set_text_color()
{
    
}

_INLINE_ void vm_inst_set_text_size()
{
    
}

_INLINE_ void vm_inst_set_text_wrap()
{
    
}

_INLINE_ void vm_inst_set_font()
{
    
}

_INLINE_ void vm_inst_print_chr()
{
    
}

_INLINE_ void vm_inst_print_str()
{
    
}

_INLINE_ void vm_inst_print_int()
{
    
}

_INLINE_ void vm_inst_printf_str()
{
    
}

_INLINE_ void vm_inst_draw_image()
{
    
}

_INLINE_ void vm_inst_load_prg()
{
    
}

_INLINE_ void vm_inst_mem_set()
{
    
}
