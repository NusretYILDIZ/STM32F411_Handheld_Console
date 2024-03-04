#include "./instructions.h"
#include "./script_engine.h"
#include "./mem_access_def.h"
#include <math.h>

#define __inline  __attribute__((always_inline)) inline 

__inline void vm_inst_syscall()
{
    
}

__inline void vm_inst_assign()
{
	++prg_counter;
	
	uint8_t dest_addr_mode, dest_data_type, oper_mode;
	read_attrib(dest_addr_mode, dest_data_type, oper_mode);
	
	ram_t dest_addr;
	read_addr(dest_addr, dest_addr_mode);
	
	uint8_t src_addr_mode, src_data_type;
	read_attrib(src_addr_mode, src_data_type, oper_mode);
	
	ram_t src_addr;
	set_read_addr(src_addr, src_addr_mode, src_data_type);
	
	mem_buf tmp;
	
	switch(src_data_type)
	{
	case TYPE_FLOAT:
		tmp.flt = ram_ptr_float(src_addr);
		break;
	
	case TYPE_INT32:
		tmp.int32 = ram_ptr_int32(src_addr);
		break;
	
	case TYPE_INT16:
		tmp.int16 = ram_ptr_int16(src_addr);
		break;
	
	case TYPE_INT8:
		tmp.int8 = ram_ptr_int8(src_addr);
		break;
	
	case TYPE_UINT32:
		tmp.uint32 = ram_ptr_uint32(src_addr);
		break;
	
	case TYPE_UINT16:
		tmp.uint16 = ram_ptr_uint16(src_addr);
		break;
	
	case TYPE_UINT8:
		tmp.uint8 = ram_ptr_uint8(src_addr);
		break;
	}
	
	switch(dest_data_type)
	{
	case TYPE_FLOAT:
		write_float(tmp.flt, dest_addr);
		break;
	
	case TYPE_INT32:
		write_int32(tmp.int32, dest_addr);
		break;
	
	case TYPE_INT16:
		write_int16(tmp.int16, dest_addr);
		break;
	
	case TYPE_INT8:
		write_int8(tmp.int8, dest_addr);
		break;
	
	case TYPE_UINT32:
		write_uint32(tmp.uint32, dest_addr);
		break;
	
	case TYPE_UINT16:
		write_uint16(tmp.uint16, dest_addr);
		break;
	
	case TYPE_UINT8:
		write_uint8(tmp.uint8, dest_addr);
		break;
	}
}

__inline void vm_inst_arith_calc()
{
	++prg_counter;
	
	uint8_t dest_addr_mode, dest_data_type, dest_oper_mode;
	read_attrib(dest_addr_mode, dest_data_type, dest_oper_mode);
	
	ram_t dest_addr;
	read_addr(dest_addr, dest_addr_mode);
	
	mem_buf res;
	uint8_t float_flag = 0, first_flag = 1;
	
	for(;;)
	{
		uint8_t opr_addr_mode, opr_data_type, opr_oper_mode;
		read_attrib(opr_addr_mode, opr_data_type, opr_oper_mode);
		
		if(opr_data_type == TYPE_TERMINATE) break;
		
		ram_t opr_addr;
		set_read_addr(opr_addr, opr_addr_mode, opr_data_type);
		
		mem_buf opr_data;
		
		if(opr_data_type == TYPE_FLOAT && !float_flag)
		{
			float_flag = 1;
			res.flt = (float) res.int32;
		}
		
		if(float_flag)
		{
			switch(opr_data_type)
			{
			case TYPE_FLOAT:
				opr_data.flt = ram_ptr_float(opr_addr);
				break;
			
			case TYPE_INT32:
				opr_data.flt = (float) ram_ptr_int32(opr_addr);
				break;
			
			case TYPE_INT16:
				opr_data.flt = (float) ram_ptr_int16(opr_addr);
				break;
			
			case TYPE_INT8:
				opr_data.flt = (float) ram_ptr_int8(opr_addr);
				break;
			
			case TYPE_UINT32:
				opr_data.flt = (float) ram_ptr_uint32(opr_addr);
				break;
			
			case TYPE_UINT16:
				opr_data.flt = (float) ram_ptr_uint16(opr_addr);
				break;
			
			case TYPE_UINT8:
				opr_data.flt = (float) ram_ptr_uint8(opr_addr);
				break;
			}
			
			if(first_flag)
			{
				first_flag = 0;
				res.flt = opr_data.flt;
			}
			else
			{
				switch(opr_oper_mode)
				{
				case ARITH_ADD:
					res.flt += opr_data.flt;
					break;
				
				case ARITH_SUB:
					res.flt -= opr_data.flt;
					break;
				
				case ARITH_MUL:
					res.flt *= opr_data.flt;
					break;
				
				case ARITH_DIV:
					res.flt /= opr_data.flt;
					break;
				
				case ARITH_MOD:
					// Kernel panic. Cannot do modulo with floats.
					break;
				
				case ARITH_POW:
					res.flt = powf(res.flt, opr_data.flt);
					break;
				}
			}
		}
		else
		{
			//printf("float_flag == 0\nopr_addr = %d\n\n", opr_addr);
			switch(opr_data_type)
			{
			case TYPE_FLOAT: // I believe this case is impossible because if operand type is float then we set float_flag immediately.
				opr_data.int32 = (int32_t) ram_ptr_float(opr_addr);
				break;
			
			case TYPE_INT32:
				opr_data.int32 = ram_ptr_int32(opr_addr);
				break;
			
			case TYPE_INT16:
				opr_data.int32 = (int32_t) ram_ptr_int16(opr_addr);
				break;
			
			case TYPE_INT8:
				opr_data.int32 = (int32_t) ram_ptr_int8(opr_addr);
				break;
			
			case TYPE_UINT32:
				opr_data.int32 = (int32_t) ram_ptr_uint32(opr_addr);
				break;
			
			case TYPE_UINT16:
				opr_data.int32 = (int32_t) ram_ptr_uint16(opr_addr);
				break;
			
			case TYPE_UINT8:
				opr_data.int32 = (int32_t) ram_ptr_uint8(opr_addr);
				break;
			}
			
			if(first_flag)
			{
				first_flag = 0;
				res.int32 = opr_data.int32;
			}
			else
			{
				switch(opr_oper_mode)
				{
				case ARITH_ADD:
					res.int32 += opr_data.int32;
					break;

				case ARITH_SUB:
					res.int32 -= opr_data.int32;
					break;

				case ARITH_MUL:
					res.int32 *= opr_data.int32;
					break;

				case ARITH_DIV:
					res.int32 /= opr_data.int32;
					break;

				case ARITH_MOD:
					res.int32 %= opr_data.int32;
					break;

				case ARITH_POW:
					res.int32 = (int32_t) powf((float) res.int32, (float) opr_data.int32);
					break;
				}
			}
		}
		
		//printf("opr_data.flt = %f\nopr_data.int32 = %d\nopr_data.int16 = %d\nopr_data.int8 = %d\nopr_data.uint32 = %d\nopr_data.uint16 = %d\nopr_data.uint8 = %d\n\n",
		//		opr_data.flt, opr_data.int32, opr_data.int16, opr_data.int8, opr_data.uint32, opr_data.uint16, opr_data.uint8);
	}
	
	switch(dest_data_type)
	{
	case TYPE_FLOAT:
		write_float(res.flt, dest_addr);
		break;
	
	case TYPE_INT32:
		write_int32(res.int32, dest_addr);
		break;
	
	case TYPE_INT16:
		write_int16(res.int16, dest_addr);
		break;
	
	case TYPE_INT8:
		write_int8(res.int8, dest_addr);
		break;
	
	case TYPE_UINT32:
		write_uint32(res.uint32, dest_addr);
		break;
	
	case TYPE_UINT16:
		write_uint16(res.uint16, dest_addr);
		break;
	
	case TYPE_UINT8:
		write_uint8(res.uint8, dest_addr);
		break;
	}
}

/*__inline void vm_inst_arith_calc()
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
}*/

__inline void vm_inst_bitwise()
{
    
}

__inline void vm_inst_logical()
{
    
}

__inline void vm_inst_jsr()
{
    ++prg_counter;
    
    ram_t jmp_addr = *(ram_t *) (&ram[prg_counter]);
    prg_counter += sizeof(ram_t);
    
    vm_push(prg_counter);
    prg_counter = jmp_addr;
}

__inline void vm_inst_rts()
{
    prg_counter = (ram_t) vm_pop();
}

__inline void vm_inst_jump_if()
{
    ++prg_counter;
    
    if(logical_flag)
        prg_counter = *(ram_t *) (&ram[prg_counter]);
    else
        prg_counter += sizeof(ram_t);
}

__inline void vm_inst_jump()
{
    ++prg_counter;
    prg_counter = *(ram_t *) (&ram[prg_counter]);
}

__inline void vm_inst_exit()
{
    
}

__inline void vm_inst_set_text_area()
{
    
}

__inline void vm_inst_set_cursor()
{
    
}

__inline void vm_inst_set_text_color()
{
    
}

__inline void vm_inst_set_text_size()
{
    
}

__inline void vm_inst_set_text_wrap()
{
    
}

__inline void vm_inst_set_font()
{
    
}

__inline void vm_inst_print_chr()
{
    
}

__inline void vm_inst_print_str()
{
    
}

__inline void vm_inst_print_int()
{
    
}

__inline void vm_inst_printf_str()
{
    
}

__inline void vm_inst_draw_image()
{
    
}

__inline void vm_inst_load_prg()
{
    
}

__inline void vm_inst_mem_set()
{
    
}
