#include "./instructions.h"
#include "./script_engine.h"
#include "./mem_access_def.h"
#include "../game_engine.h"
#include "../../input/input_driver.h"
#include <math.h>
#include <string.h>

#define __inline  __attribute__((always_inline)) inline

__inline void read_memory(RAM_PTR *addr, void *dest, uint8_t var_type)
{
	switch(var_type)
	{
	case TYPE_TERMINATE:
		break;
	
	case TYPE_FLOAT:
		if(dest) *(float *)dest = *(float *)(&ram[*addr]);
		*addr += sizeof(float);
		break;
	
	case TYPE_INT32:
		if(dest) *(int32_t *)dest = *(int32_t *)(&ram[*addr]);
		*addr += sizeof(int32_t);
		break;
	
	case TYPE_UINT32:
		if(dest) *(uint32_t *)dest = *(uint32_t *)(&ram[*addr]);
		*addr += sizeof(uint32_t);
		break;
	
	case TYPE_INT16:
		if(dest) *(int16_t *)dest = *(int16_t *)(&ram[*addr]);
		*addr += sizeof(int16_t);
		break;
	
	case TYPE_UINT16:
		if(dest) *(uint16_t *)dest = *(uint16_t *)(&ram[*addr]);
		*addr += sizeof(uint16_t);
		break;
	
	case TYPE_INT8:
		if(dest) *(int8_t *)dest = *(int8_t *)(&ram[*addr]);
		*addr += sizeof(int8_t);
		break;
	
	case TYPE_UINT8:
		if(dest) *(uint8_t *)dest = *(uint8_t *)(&ram[*addr]);
		*addr += sizeof(uint8_t);
		break;
	
	case TYPE_RAM_PTR:
		if(dest) *(RAM_PTR *)dest = *(RAM_PTR *)(&ram[*addr]);
		*addr += sizeof(RAM_PTR);
		break;
	
	case TYPE_STRING:
		if(dest) *(RAM_PTR *)dest = *addr;
		while(ram[(*addr) - 1] != '\0') (*addr)++;
		break;
	
	default:
		KERNEL_PANIC(PANIC_UNKNOWN_DATA_TYPE);
		break;
	}
}

__inline TYPE_FLAG read_param(void *dest)
{
	uint8_t var_attr = ram[prg_counter];
	prg_counter++;
	
	TYPE_FLAG type_flag = var_attr & TYPE_MASK;
	
	if(var_attr & ADDR_IMM)
	{
		read_memory(&prg_counter, dest, type_flag);
	}
	else if(var_attr & ADDR_ABS)
	{
		RAM_PTR var_addr = *(RAM_PTR *)(&ram[prg_counter]);
		prg_counter += sizeof(RAM_PTR);
		
		read_memory(&var_addr, dest, type_flag);
	}
	else if(var_attr & ADDR_PTR)
	{
		RAM_PTR var_addr = *(RAM_PTR *)(&ram[prg_counter]);
		prg_counter += sizeof(RAM_PTR);
		
		var_addr = *(RAM_PTR *)(&ram[var_addr]);
		
		read_memory(&var_addr, dest, type_flag);
	}
	else 
	{
		//printf("addr_mode = %d\n", var_attr & ADDR_MASK);
		KERNEL_PANIC(PANIC_UNKNOWN_ADDR_MODE);
	}
	
	return type_flag;
}

__inline TYPE_FLAG read_addr(RAM_PTR *dest)
{
	uint8_t var_attr = ram[prg_counter];
	prg_counter++;
	
	TYPE_FLAG type_flag = var_attr & TYPE_MASK;
	
	if(var_attr & ADDR_IMM) 
	{
		if(dest) *dest = prg_counter;
		prg_counter += sizeof(RAM_PTR);
	}
	else if(var_attr & ADDR_ABS)
	{
		if(dest) *dest = *(RAM_PTR *)(&ram[prg_counter]);
		prg_counter += sizeof(RAM_PTR);
	}
	else if(var_attr & ADDR_PTR)
	{
		if(dest) *dest = *(RAM_PTR *)(&ram[prg_counter]);
		prg_counter += sizeof(RAM_PTR);
		
		*dest = *(RAM_PTR *)(&ram[*dest]);
	}
	else 
	{
		//printf("addr_mode = %d\n", var_attr & ADDR_MASK);
		KERNEL_PANIC(PANIC_UNKNOWN_ADDR_MODE);
	}
	
	return type_flag;
}

__inline void copy_data(TYPE_FLAG data_type, RAM_PTR dest, MEM_BUF src)
{
	switch(data_type)
	{
	case TYPE_FLOAT:
		*(float *)(&ram[dest]) = src.flt;
		break;
	
	case TYPE_INT32:
		*(int32_t *)(&ram[dest]) = src.int32;
		break;
	
	case TYPE_UINT32:
		*(uint32_t *)(&ram[dest]) = src.uint32;
		break;
	
	case TYPE_INT16:
		*(int16_t *)(&ram[dest]) = src.int16;
		break;
	
	case TYPE_UINT16:
		*(uint16_t *)(&ram[dest]) = src.uint16;
		break;
	
	case TYPE_INT8:
		*(int8_t *)(&ram[dest]) = src.int8;
		break;
	
	case TYPE_UINT8:
		*(uint8_t *)(&ram[dest]) = src.uint8;
		break;
	
	case TYPE_RAM_PTR:
		*(RAM_PTR *)(&ram[dest]) = src.ram_ptr;
		break;
	
	default:
		KERNEL_PANIC(PANIC_UNKNOWN_DATA_TYPE);
		break;
	}
}


__inline void vm_inst_invalid()
{
	KERNEL_PANIC(PANIC_INVALID_INSTRUCTION);
}

__inline void vm_inst_syscall()
{
    
}

__inline void vm_inst_assign()
{
	RAM_PTR dest_addr;
	TYPE_FLAG dest_type = read_addr(&dest_addr);
	
	MEM_BUF data;
	TYPE_FLAG data_type = read_param(&data);
	
	if(dest_type == data_type)
		copy_data(data_type, dest_addr, data);
	
	else
	{
		KERNEL_PANIC(PANIC_DATA_TYPE_DISCREPANCY);
	}
	
	/*uint8_t dest_addr_mode, dest_data_type, oper_mode;
	read_attrib(dest_addr_mode, dest_data_type, oper_mode);
	
	RAM_PTR dest_addr;
	read_addr(dest_addr, dest_addr_mode);
	
	uint8_t src_addr_mode, src_data_type;
	read_attrib(src_addr_mode, src_data_type, oper_mode);
	
	RAM_PTR src_addr;
	set_read_addr(src_addr, src_addr_mode, src_data_type);
	
	MEM_BUF tmp;
	
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
		////printf("tmp.flt = %f\n", tmp.flt);
		
		if(tmp.flt == 0.0f) logical_flag |=  ZERO_FLAG;
		else                logical_flag &= ~ZERO_FLAG;
		
		if(tmp.flt < 0.0f)  logical_flag |=  SIGN_FLAG;
		else                logical_flag &= ~SIGN_FLAG;
		
		break;
	
	case TYPE_INT32:
		write_int32(tmp.int32, dest_addr);
		
		if(tmp.int32 == 0) logical_flag |=  ZERO_FLAG;
		else               logical_flag &= ~ZERO_FLAG;
		
		if(tmp.int32 < 0)  logical_flag |=  SIGN_FLAG;
		else               logical_flag &= ~SIGN_FLAG;
		
		break;
	
	case TYPE_INT16:
		write_int16(tmp.int16, dest_addr);
		
		if(tmp.int16 == 0) logical_flag |=  ZERO_FLAG;
		else               logical_flag &= ~ZERO_FLAG;
		
		if(tmp.int16 < 0)  logical_flag |=  SIGN_FLAG;
		else               logical_flag &= ~SIGN_FLAG;
		
		break;
	
	case TYPE_INT8:
		write_int8(tmp.int8, dest_addr);
		
		if(tmp.int8 == 0) logical_flag |=  ZERO_FLAG;
		else              logical_flag &= ~ZERO_FLAG;
		
		if(tmp.int8 < 0)  logical_flag |=  SIGN_FLAG;
		else              logical_flag &= ~SIGN_FLAG;
		
		break;
	
	case TYPE_UINT32:
		write_uint32(tmp.uint32, dest_addr);
		
		if(tmp.uint32 == 0) logical_flag |=  ZERO_FLAG;
		else                logical_flag &= ~ZERO_FLAG;
		
		break;
	
	case TYPE_UINT16:
		write_uint16(tmp.uint16, dest_addr);
		
		if(tmp.uint16 == 0) logical_flag |=  ZERO_FLAG;
		else                logical_flag &= ~ZERO_FLAG;
		
		break;
	
	case TYPE_UINT8:
		write_uint8(tmp.uint8, dest_addr);
		
		if(tmp.uint8 == 0) logical_flag |=  ZERO_FLAG;
		else               logical_flag &= ~ZERO_FLAG;
		
		break;
	}*/
}

__inline void vm_inst_increase()
{
	RAM_PTR var_addr;
	TYPE_FLAG data_type = read_addr(&var_addr);
	
	switch(data_type)
	{
	case TYPE_INT32:
		(*(int32_t *)(&ram[var_addr]))++;
		break;
		
	case TYPE_UINT32:
		(*(uint32_t *)(&ram[var_addr]))++;
		break;
		
	case TYPE_INT16:
		(*(int16_t *)(&ram[var_addr]))++;
		break;
		
	case TYPE_UINT16:
		(*(uint16_t *)(&ram[var_addr]))++;
		break;
		
	case TYPE_INT8:
		(*(int8_t *)(&ram[var_addr]))++;
		break;
		
	case TYPE_UINT8:
		(*(uint8_t *)(&ram[var_addr]))++;
		break;
	
	default:
		KERNEL_PANIC(PANIC_UNKNOWN_DATA_TYPE);
		break;
	}
}

__inline void vm_inst_decrease()
{
	RAM_PTR var_addr;
	TYPE_FLAG data_type = read_addr(&var_addr);
	
	switch(data_type)
	{
	case TYPE_INT32:
		(*(int32_t *)(&ram[var_addr]))--;
		break;
		
	case TYPE_UINT32:
		(*(uint32_t *)(&ram[var_addr]))--;
		break;
		
	case TYPE_INT16:
		(*(int16_t *)(&ram[var_addr]))--;
		break;
		
	case TYPE_UINT16:
		(*(uint16_t *)(&ram[var_addr]))--;
		break;
		
	case TYPE_INT8:
		(*(int8_t *)(&ram[var_addr]))--;
		break;
		
	case TYPE_UINT8:
		(*(uint8_t *)(&ram[var_addr]))--;
		break;
	
	default:
		KERNEL_PANIC(PANIC_UNKNOWN_DATA_TYPE);
		break;
	}
}

__inline void vm_inst_arith_calc()
{
	//printf("Arithmetic calculation inst.\n\n");
	
	/*uint8_t dest_addr_mode, dest_data_type, dest_oper_mode;
	read_attrib(dest_addr_mode, dest_data_type, dest_oper_mode);
	
	RAM_PTR dest_addr;
	read_addr(dest_addr, dest_addr_mode);
	
	MEM_BUF res;
	uint8_t float_flag = 0, first_flag = 1;
	
	for(;;)
	{
		uint8_t opr_addr_mode, opr_data_type, opr_oper_mode;
		read_attrib(opr_addr_mode, opr_data_type, opr_oper_mode);
		
		if(opr_data_type == TYPE_TERMINATE) break;
		
		RAM_PTR opr_addr;
		set_read_addr(opr_addr, opr_addr_mode, opr_data_type);
		
		MEM_BUF opr_data;
		
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
	}
	
	switch(dest_data_type)
	{
	case TYPE_FLOAT:
		write_float(res.flt, dest_addr);
		////printf("res.flt = %f\n", res.flt);
		
		if(res.flt == 0.0f) logical_flag |=  ZERO_FLAG;
		else                logical_flag &= ~ZERO_FLAG;
		
		if(res.flt < 0.0f)  logical_flag |=  SIGN_FLAG;
		else                logical_flag &= ~SIGN_FLAG;
		
		break;
	
	case TYPE_INT32:
		write_int32(res.int32, dest_addr);
		
		if(res.int32 == 0) logical_flag |=  ZERO_FLAG;
		else               logical_flag &= ~ZERO_FLAG;
		
		if(res.int32 < 0)  logical_flag |=  SIGN_FLAG;
		else               logical_flag &= ~SIGN_FLAG;
		
		break;
	
	case TYPE_INT16:
		write_int16(res.int16, dest_addr);
		
		if(res.int16 == 0) logical_flag |=  ZERO_FLAG;
		else               logical_flag &= ~ZERO_FLAG;
		
		if(res.int16 < 0)  logical_flag |=  SIGN_FLAG;
		else               logical_flag &= ~SIGN_FLAG;
		
		break;
	
	case TYPE_INT8:
		write_int8(res.int8, dest_addr);
		
		if(res.int8 == 0) logical_flag |=  ZERO_FLAG;
		else              logical_flag &= ~ZERO_FLAG;
		
		if(res.int8 < 0)  logical_flag |=  SIGN_FLAG;
		else              logical_flag &= ~SIGN_FLAG;
		
		break;
	
	case TYPE_UINT32:
		write_uint32(res.uint32, dest_addr);
		
		if(res.uint32 == 0) logical_flag |=  ZERO_FLAG;
		else                logical_flag &= ~ZERO_FLAG;
		
		break;
	
	case TYPE_UINT16:
		write_uint16(res.uint16, dest_addr);
		
		if(res.uint16 == 0) logical_flag |=  ZERO_FLAG;
		else                logical_flag &= ~ZERO_FLAG;
		
		break;
	
	case TYPE_UINT8:
		write_uint8(res.uint8, dest_addr);
		
		if(res.uint8 == 0) logical_flag |=  ZERO_FLAG;
		else               logical_flag &= ~ZERO_FLAG;
		
		break;
	}*/
}

__inline void vm_inst_bitwise()
{
    /*uint8_t dest_addr_mode, dest_data_type, dest_oper_mode;
	read_attrib(dest_addr_mode, dest_data_type, dest_oper_mode);
	
	RAM_PTR dest_addr;
	read_addr(dest_addr, dest_addr_mode);
	
	MEM_BUF res;
	uint8_t first_flag = 1;
	
	for(;;)
	{
		uint8_t opr_addr_mode, opr_data_type, opr_oper_mode;
		read_attrib(opr_addr_mode, opr_data_type, opr_oper_mode);
		
		if(opr_data_type == TYPE_TERMINATE) break;
		
		RAM_PTR opr_addr;
		set_read_addr(opr_addr, opr_addr_mode, opr_data_type);
		
		MEM_BUF opr_data;
		
		if(opr_oper_mode != BITWISE_NOT)
		{
			switch(opr_data_type)
			{
			case TYPE_FLOAT:
				// Kernel panic. Cannot do bitwise operations with floats.
				break;
			
			case TYPE_INT32:
				opr_data.int32 = ram_ptr_int32(opr_addr);
				break;
			
			case TYPE_INT16:
				opr_data.int32 = ram_ptr_int16(opr_addr);
				break;
			
			case TYPE_INT8:
				opr_data.int32 = ram_ptr_int8(opr_addr);
				break;
			
			case TYPE_UINT32:
				opr_data.int32 = ram_ptr_uint32(opr_addr);
				break;
			
			case TYPE_UINT16:
				opr_data.int32 = ram_ptr_uint16(opr_addr);
				break;
			
			case TYPE_UINT8:
				opr_data.int32 = ram_ptr_uint8(opr_addr);
				break;
			}
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
			case BITWISE_AND:
				res.int32 &= opr_data.int32;
				break;
			
			case BITWISE_OR:
				res.int32 |= opr_data.int32;
				break;
			
			case BITWISE_XOR:
				res.int32 ^= opr_data.int32;
				break;
			
			case BITWISE_NOT:
				res.int32 = ~res.int32;
				break;
			
			case BITWISE_SHL:
				res.int32 <<= opr_data.int32;
				break;
			
			case BITWISE_SHR:
				res.int32 >>= opr_data.int32;
				break;
			}
		}
	}
	
	switch(dest_data_type)
	{
	case TYPE_FLOAT:
		// Kernel panic. Cannot do bitwise operations with floats.
		break;
	
	case TYPE_INT32:
		write_int32(res.int32, dest_addr);
		
		if(res.int32) logical_flag &= ~ZERO_FLAG;
		else          logical_flag |=  ZERO_FLAG;
		
		if(res.int32 < 0) logical_flag |=  SIGN_FLAG;
		else              logical_flag &= ~SIGN_FLAG;
		
		break;
	
	case TYPE_INT16:
		write_int16(res.int16, dest_addr);
		
		if(res.int16) logical_flag &= ~ZERO_FLAG;
		else          logical_flag |=  ZERO_FLAG;
		
		if(res.int16 < 0) logical_flag |=  SIGN_FLAG;
		else              logical_flag &= ~SIGN_FLAG;
		
		break;
	
	case TYPE_INT8:
		write_int8(res.int8, dest_addr);
		
		if(res.int8) logical_flag &= ~ZERO_FLAG;
		else         logical_flag |=  ZERO_FLAG;
		
		if(res.int8 < 0) logical_flag |=  SIGN_FLAG;
		else             logical_flag &= ~SIGN_FLAG;
		
		break;
	
	case TYPE_UINT32:
		write_uint32(res.uint32, dest_addr);
		
		if(res.uint32) logical_flag &= ~ZERO_FLAG;
		else           logical_flag |=  ZERO_FLAG;
		
		break;
	
	case TYPE_UINT16:
		write_uint16(res.uint16, dest_addr);
		
		if(res.uint16 < 0) logical_flag |=  SIGN_FLAG;
		else               logical_flag &= ~SIGN_FLAG;
		
		break;
	
	case TYPE_UINT8:
		write_uint8(res.uint8, dest_addr);
		
		if(res.uint8 < 0) logical_flag |=  SIGN_FLAG;
		else              logical_flag &= ~SIGN_FLAG;
		
		break;
	}*/
}

__inline void vm_inst_logical()
{
    /*uint8_t dest_addr_mode, dest_data_type, dest_oper_mode;
	read_attrib(dest_addr_mode, dest_data_type, dest_oper_mode);
	
	RAM_PTR dest_addr;
	read_addr(dest_addr, dest_addr_mode);
	
	MEM_BUF tmp;
	uint8_t res, first_flag = 1;
	
	for(;;)
	{
		uint8_t opr_addr_mode, opr_data_type, opr_oper_mode;
		read_attrib(opr_addr_mode, opr_data_type, opr_oper_mode);
		
		if(opr_data_type == TYPE_TERMINATE) break;
		
		RAM_PTR opr_addr;
		set_read_addr(opr_addr, opr_addr_mode, opr_data_type);
		
		MEM_BUF opr_data;
		
		if(opr_oper_mode != LOGICAL_NOT)
		{
			switch(opr_data_type)
			{
			case TYPE_FLOAT:
				opr_data.flt = ram_ptr_float(opr_addr);
				break;
				
			case TYPE_INT32:
				opr_data.int32 = ram_ptr_int32(opr_addr);
				break;
				
			case TYPE_INT16:
				opr_data.int32 = ram_ptr_int16(opr_addr);
				break;
				
			case TYPE_INT8:
				opr_data.int32 = ram_ptr_int8(opr_addr);
				break;
				
			case TYPE_UINT32:
				opr_data.int32 = ram_ptr_uint32(opr_addr);
				break;
				
			case TYPE_UINT16:
				opr_data.int32 = ram_ptr_uint16(opr_addr);
				break;
				
			case TYPE_UINT8:
				opr_data.int32 = ram_ptr_uint8(opr_addr);
				break;
			}
		}
		
		if(first_flag)
		{
			first_flag = 0;
			res = (opr_data.flt) ? 1 : 0;
			tmp.flt = opr_data.flt;
		}
		else
		{
			switch(opr_oper_mode)
			{
			case LOGICAL_AND:
				//if(opr_data_type != TYPE_FLOAT) tmp.int32 &= opr_data.int32;
				//res = (tmp.int32) ? 1 : 0;
				if(opr_data_type == TYPE_FLOAT) res &= (tmp.flt) ? 1 : 0;
				else res &= (tmp.int32) ? 1 : 0;
				break;
			
			case LOGICAL_OR:
				//if(opr_data_type != TYPE_FLOAT) tmp.int32 |= opr_data.int32;
				//res = (tmp.int32) ? 1 : 0;
				if(opr_data_type == TYPE_FLOAT) res |= (tmp.flt) ? 1 : 0;
				else res |= (tmp.int32) ? 1 : 0;
				break;
			
			case LOGICAL_NOT:
				res = !res;
				break;
			
			case LOGICAL_EQUAL:
				if(opr_data_type == TYPE_FLOAT) res = (tmp.flt == opr_data.flt);
				else res = (tmp.int32 == opr_data.int32);
				break;
			
			case LOGICAL_LESS:
				if(opr_data_type == TYPE_FLOAT) res = (tmp.flt < opr_data.flt);
				else res = (tmp.int32 < opr_data.int32);
				break;
			
			case LOGICAL_GREAT:
				if(opr_data_type == TYPE_FLOAT) res = (tmp.flt > opr_data.flt);
				else res = (tmp.int32 > opr_data.int32);
				break;
			
			case LOGICAL_LESSEQ:
				if(opr_data_type == TYPE_FLOAT) res = (tmp.flt <= opr_data.flt);
				else res = (tmp.int32 <= opr_data.int32);
				break;
			
			case LOGICAL_GREATEQ:
				if(opr_data_type == TYPE_FLOAT) res = (tmp.flt >= opr_data.flt);
				else res = (tmp.int32 >= opr_data.int32);
				break;
			}
		}
	}
	
	if(dest_data_type == TYPE_UINT8)
	{
		write_uint8(res, dest_addr);
	}
	
	if(res) logical_flag &= ~ZERO_FLAG;
	else    logical_flag |=  ZERO_FLAG;*/
}

__inline void vm_inst_jsr()
{
    RAM_PTR jmp_addr = *(RAM_PTR *) (&ram[prg_counter]);
    prg_counter += sizeof(RAM_PTR);
    
    vm_push(prg_counter);
    prg_counter = jmp_addr;
}

__inline void vm_inst_rts()
{
    prg_counter = (RAM_PTR) vm_pop();
}

__inline void vm_inst_jump_if_carry()
{
	RAM_PTR jump_addr;
	read_addr(&jump_addr);
		
	if(status_flag & CARRY_FLAG)
	{
		jump_addr += engine_settings.game_code_addr;
		prg_counter = jump_addr;
	}
}

__inline void vm_inst_jump_if_zero()
{
	RAM_PTR jump_addr;
	read_addr(&jump_addr);
		
	if(status_flag & ZERO_FLAG)
	{
		jump_addr += engine_settings.game_code_addr;
		prg_counter = jump_addr;
	}
}

__inline void vm_inst_jump_if()
{
    /*if(logical_flag)
        prg_counter = *(RAM_PTR *) (&ram[prg_counter]);
    else
        prg_counter += sizeof(RAM_PTR);*/
}

__inline void vm_inst_jump()
{
	RAM_PTR jump_addr;
	read_addr(&jump_addr);
	jump_addr += engine_settings.game_code_addr;
	
	prg_counter = jump_addr;
    //prg_counter = ram_ptr_addr(prg_counter);
}

// Exit from game and return to system menu.
__inline void vm_inst_exit_game()
{
    status_flag |= EXIT_GAME_FLAG;
}

__inline void vm_inst_set_text_area()
{
	int16_t sx, sy, ex, ey;
	
	TYPE_FLAG data_type = read_param(&sx);
	if(data_type != TYPE_INT16) 
	{
		KERNEL_PANIC(PANIC_DATA_TYPE_DISCREPANCY);
	}
	
	data_type = read_param(&sy);
	if(data_type != TYPE_INT16) 
	{
		KERNEL_PANIC(PANIC_DATA_TYPE_DISCREPANCY);
	}
	
	data_type = read_param(&ex);
	if(data_type != TYPE_INT16) 
	{
		KERNEL_PANIC(PANIC_DATA_TYPE_DISCREPANCY);
	}
	
	data_type = read_param(&ey);
	if(data_type != TYPE_INT16) 
	{
		KERNEL_PANIC(PANIC_DATA_TYPE_DISCREPANCY);
	}
	
	set_text_area(sx, sy, ex, ey);
	
    /*uint8_t src_addr_mode, src_data_type, src_oper_mode;
	RAM_PTR src_addr;
	
	int16_t sx, sy, ex, ey;
	
	// Read start X
	read_attrib(src_addr_mode, src_data_type, src_oper_mode);
	set_read_addr(src_addr, src_addr_mode, src_data_type);
	read_int16(sx, src_addr);
	
	// Read start Y
	read_attrib(src_addr_mode, src_data_type, src_oper_mode);
	set_read_addr(src_addr, src_addr_mode, src_data_type);
	read_int16(sy, src_addr);
	
	// Read end X
	read_attrib(src_addr_mode, src_data_type, src_oper_mode);
	set_read_addr(src_addr, src_addr_mode, src_data_type);
	read_int16(ex, src_addr);
	
	// Read end Y
	read_attrib(src_addr_mode, src_data_type, src_oper_mode);
	set_read_addr(src_addr, src_addr_mode, src_data_type);
	read_int16(ey, src_addr);
	
	//printf("set_text_area(%d, %d, %d, %d)\n\n", sx, sy, ex, ey);
	
	set_text_area(sx, sy, ex, ey);*/
}

__inline void vm_inst_set_cursor()
{
	int16_t x, y;
	
	TYPE_FLAG data_type = read_param(&x);
	if(data_type != TYPE_INT16) 
	{
		KERNEL_PANIC(PANIC_DATA_TYPE_DISCREPANCY);
	}
	
	data_type = read_param(&y);
	if(data_type != TYPE_INT16) 
	{
		KERNEL_PANIC(PANIC_DATA_TYPE_DISCREPANCY);
	}
	
	set_cursor(x, y);
	
    /*uint8_t src_addr_mode, src_data_type, src_oper_mode;
	RAM_PTR src_addr;
	
	int16_t x, y;

	// Read X position
	read_attrib(src_addr_mode, src_data_type, src_oper_mode);	
	set_read_addr(src_addr, src_addr_mode, src_data_type);
	read_int16(x, src_addr);
	
	// Read Y position
	read_attrib(src_addr_mode, src_data_type, src_oper_mode);
	set_read_addr(src_addr, src_addr_mode, src_data_type);
	read_int16(y, src_addr);
	
	//printf("set_cursor(%d, %d)\n\n", x, y);
	
	set_cursor(x, y);*/
}

__inline void vm_inst_set_text_color()
{
	uint8_t fg, bg;
	
	TYPE_FLAG data_type = read_param(&fg);
	if(data_type != TYPE_UINT8) 
	{
		KERNEL_PANIC(PANIC_DATA_TYPE_DISCREPANCY);
	}
	
	data_type = read_param(&bg);
	if(data_type == TYPE_TERMINATE) bg = fg;
	else if(data_type != TYPE_UINT8) 
	{
		KERNEL_PANIC(PANIC_DATA_TYPE_DISCREPANCY);
	}
	
	set_text_color(fg, bg);
	
    /*uint8_t src_addr_mode, src_data_type, src_oper_mode;
	RAM_PTR src_addr;
	
	uint8_t fg, bg;

	// Read foreground color
	read_attrib(src_addr_mode, src_data_type, src_oper_mode);	
	set_read_addr(src_addr, src_addr_mode, src_data_type);
	read_uint8(fg, src_addr);

	// Read background color
	read_attrib(src_addr_mode, src_data_type, src_oper_mode);
	
	if(src_data_type == TYPE_TERMINATE)
		bg = fg;
	else
	{
		set_read_addr(src_addr, src_addr_mode, src_data_type);
		read_uint8(bg, src_addr);
	}
	
	//printf("set_text_color(%d, %d)\n\n", fg, bg);
	
	set_text_color(fg, bg);*/
}

__inline void vm_inst_set_text_size()
{
	uint8_t x, y;
	
	TYPE_FLAG data_type = read_param(&x);
	if(data_type != TYPE_UINT8) 
	{
		KERNEL_PANIC(PANIC_DATA_TYPE_DISCREPANCY);
	}
	
	data_type = read_param(&y);
	if(data_type == TYPE_TERMINATE) y = x;
	else if(data_type != TYPE_UINT8) 
	{
		KERNEL_PANIC(PANIC_DATA_TYPE_DISCREPANCY);
	}
	
	set_text_size(x, y);
	
    /*uint8_t src_addr_mode, src_data_type, src_oper_mode;
	RAM_PTR src_addr;
	
	uint8_t x, y;
	
	// Read X size
	read_attrib(src_addr_mode, src_data_type, src_oper_mode);
	set_read_addr(src_addr, src_addr_mode, src_data_type);
	read_uint8(x, src_addr);
	
	// Read Y size
	read_attrib(src_addr_mode, src_data_type, src_oper_mode);
	
	if(src_data_type == TYPE_TERMINATE)
		y = x;
	else
	{
		set_read_addr(src_addr, src_addr_mode, src_data_type);
		read_uint8(y, src_addr);
	}
	
	//printf("set_text_size(%d, %d)\n\n", x, y);
	
	set_text_size(x, y);*/
}

// The text that doesn't fit in text area now pushed into next line.
__inline void vm_inst_set_text_wrap()
{
    set_text_wrap(1);
}

// The text that doesn't fit in text area is now clipped.
__inline void vm_inst_clr_text_wrap()
{
    set_text_wrap(0);
}

// Set font of text for printing into VRAM.
__inline void vm_inst_set_font()
{
	uint8_t font;
	
	TYPE_FLAG data_type = read_param(&font);
	if(data_type != TYPE_UINT8) 
	{
		KERNEL_PANIC(PANIC_DATA_TYPE_DISCREPANCY);
	}
	
	set_font(font);
	
    /*uint8_t font;
	read_uint8(font, prg_counter);
	++prg_counter;
	
	set_font(font);*/
}

// Print a single character into VRAM.
__inline void vm_inst_print_chr()
{
	uint8_t chr;
	
	TYPE_FLAG data_type = read_param(&chr);
	if(data_type != TYPE_UINT8) 
	{
		KERNEL_PANIC(PANIC_DATA_TYPE_DISCREPANCY);
	}
	
	print_chr(chr);
	
    /*uint8_t src_addr_mode, src_data_type, src_oper_mode;
	read_attrib(src_addr_mode, src_data_type, src_oper_mode);
	
	RAM_PTR src_addr;
	read_addr(src_addr, src_addr_mode);
	
	print_chr(ram_ptr_uint8(src_addr));*/
}

// Print a string into VRAM.
__inline void vm_inst_print_str()
{
	RAM_PTR str_addr;
	
	TYPE_FLAG data_type = read_param(&str_addr);
	if(data_type != TYPE_STRING) 
	{
		KERNEL_PANIC(PANIC_DATA_TYPE_DISCREPANCY);
	}
	
	print_str(&ram[str_addr]);
	
    /*uint8_t src_addr_mode, src_data_type, src_oper_mode;
	RAM_PTR src_addr;
	
	read_attrib(src_addr_mode, src_data_type, src_oper_mode);
	
	if(src_addr_mode == ADDR_IMM)
	{
		src_addr = prg_counter;
		while(ram[prg_counter] != '\0') ++prg_counter;
		++prg_counter;
	}
	else
	{
		read_addr(src_addr, src_addr_mode);
	}
	
	//printf("print_str(\"%s\")\n\n", &ram[src_addr]);
	
	print_str(&ram[src_addr]);*/
}

// Print a integer into VRAM.
__inline void vm_inst_print_int()
{
	MEM_BUF number;
	TYPE_FLAG data_type = read_param(&number);
	
	switch(data_type)
	{
	case TYPE_INT32:
		print_int(number.int32);
		break;
		
	case TYPE_UINT32:
		print_int(number.uint32);
		break;
		
	case TYPE_INT16:
		print_int(number.int16);
		break;
		
	case TYPE_UINT16:
		print_int(number.uint16);
		break;
		
	case TYPE_INT8:
		print_int(number.int8);
		break;
		
	case TYPE_UINT8:
		print_int(number.uint8);
		break;
	
	default:
		KERNEL_PANIC(PANIC_UNKNOWN_DATA_TYPE);
		break;
	}
	
    /*uint8_t src_addr_mode, src_data_type, src_oper_mode;
	read_attrib(src_addr_mode, src_data_type, src_oper_mode);
	
	RAM_PTR src_addr;
	set_read_addr(src_addr, src_addr_mode, src_data_type);
	
	MEM_BUF tmp;
	
	switch(src_data_type)
	{
	case TYPE_FLOAT:
		// Kernel panic. This instruction cannot print floats.
		break;
	
	case TYPE_INT32:
		tmp.int32 = ram_ptr_int32(src_addr);
		break;
	
	case TYPE_INT16:
		tmp.int32 = (int32_t) ram_ptr_int16(src_addr);
		break;
	
	case TYPE_INT8:
		tmp.int32 = (int32_t) ram_ptr_int8(src_addr);
		break;
	
	case TYPE_UINT32:
		tmp.int32 = (int32_t) ram_ptr_uint32(src_addr);
		break;
	
	case TYPE_UINT16:
		tmp.int32 = (int32_t) ram_ptr_uint16(src_addr);
		break;
	
	case TYPE_UINT8:
		tmp.int32 = (int32_t) ram_ptr_uint8(src_addr);
		break;
	}
	
	//printf("print_int(%d)\n\n", tmp.int32);
	
	print_int(tmp.int32);*/
}

// Print a formatted text into VRAM.
__inline void vm_inst_printf_str()
{
    
}

// Copy a pixel sequence into specified VRAM coordinates.
__inline void vm_inst_draw_image()
{
    int16_t x, y;
	uint16_t w, h;
	RAM_PTR image;
	
	TYPE_FLAG data_type = read_param(&x);
	if(data_type != TYPE_INT16) 
	{
		KERNEL_PANIC(PANIC_DATA_TYPE_DISCREPANCY);
	}
	
	data_type = read_param(&y);
	if(data_type != TYPE_INT16) 
	{
		KERNEL_PANIC(PANIC_DATA_TYPE_DISCREPANCY);
	}
	
	data_type = read_param(&w);
	if(data_type != TYPE_UINT16) 
	{
		KERNEL_PANIC(PANIC_DATA_TYPE_DISCREPANCY);
	}
	
	data_type = read_param(&h);
	if(data_type != TYPE_UINT16) 
	{
		KERNEL_PANIC(PANIC_DATA_TYPE_DISCREPANCY);
	}
	
	data_type = read_addr(&image);
	if(data_type != TYPE_RAM_PTR) 
	{
		KERNEL_PANIC(PANIC_DATA_TYPE_DISCREPANCY);
	}
	
	draw_image(x, y, w, h, &ram[image], 0xff);
}

// Load a script file from SD card to RAM to execute.
__inline void vm_inst_load_prg()
{
    
}

// Set the value of specified RAM area.
__inline void vm_inst_mem_set()
{
	RAM_PTR dest, len;
	uint8_t data;
	
	TYPE_FLAG data_type = read_param(&dest);
	if(data_type != TYPE_RAM_PTR) 
	{
		KERNEL_PANIC(PANIC_DATA_TYPE_DISCREPANCY);
	}
	
	data_type = read_param(&data);
	if(data_type != TYPE_UINT8) 
	{
		KERNEL_PANIC(PANIC_DATA_TYPE_DISCREPANCY);
	}
	
	data_type = read_param(&len);
	if(data_type != TYPE_RAM_PTR) 
	{
		KERNEL_PANIC(PANIC_DATA_TYPE_DISCREPANCY);
	}
	
	memset(&ram[dest], data, len);
	
    /*uint8_t addr_mode, data_type, oper_mode;
	read_attrib(addr_mode, data_type, oper_mode);
	
	RAM_PTR dest_addr;
	read_addr(dest_addr, addr_mode);
	
	RAM_PTR val_addr;
	read_attrib(addr_mode, data_type, oper_mode);
	set_read_addr(val_addr, addr_mode, data_type);
	
	uint8_t val = ram_ptr_uint8(val_addr);
	
	RAM_PTR len_addr;
	read_attrib(addr_mode, data_type, oper_mode);
	set_read_addr(len_addr, addr_mode, data_type);
	
	RAM_PTR length = ram_ptr_addr(len_addr);
	
	//printf("mem_set(%d, %d, %d)\n\n", dest_addr, val, length);
	memset(&ram[dest_addr], val, length);*/
}

__inline void vm_inst_fill_display()
{
	uint8_t color;
	
	TYPE_FLAG data_type = read_param(&color);
	if(data_type != TYPE_UINT8) 
	{
		KERNEL_PANIC(PANIC_DATA_TYPE_DISCREPANCY);
	}
	
	fill_display(color);
}

// Update the display with VRAM content.
__inline void vm_inst_update_display()
{
    //printf("update_display()\n\n");
	update_display();
}

// Notify game engine that we reached end of game logic loop, so it can do other stuff and start over.
__inline void vm_inst_end_of_loop()
{
	// TODO: Set program counter to start of the game logic loop.
	// Second thought: Maybe we can handle it by adding a jump instruction after this, so we won't have to store address of start of loop in RAM.
	status_flag |= END_OF_LOOP_FLAG;
}

// Save specified area of RAM to specified file.
__inline void vm_inst_save_to_file()
{
    
}

// Check if a key is currently pressed.
__inline void vm_inst_get_key()
{
    uint16_t key;
	
	TYPE_FLAG data_type = read_param(&key);
	if(data_type != TYPE_UINT16) 
	{
		KERNEL_PANIC(PANIC_DATA_TYPE_DISCREPANCY);
	}
	
	if(get_key(key))
	{
		status_flag |= CARRY_FLAG;
		status_flag &= ~ZERO_FLAG;
	}
	else
	{
		status_flag &= ~CARRY_FLAG;
		status_flag |= ZERO_FLAG;
	}
}

// Check if a key is just pressed.
__inline void vm_inst_get_key_down()
{
    uint16_t key;
	
	TYPE_FLAG data_type = read_param(&key);
	if(data_type != TYPE_UINT16) 
	{
		KERNEL_PANIC(PANIC_DATA_TYPE_DISCREPANCY);
	}
	
	if(get_key_down(key))
	{
		status_flag |= CARRY_FLAG;
		status_flag &= ~ZERO_FLAG;
	}
	else
	{
		status_flag &= ~CARRY_FLAG;
		status_flag |= ZERO_FLAG;
	}
}

// Check if a key is just released.
__inline void vm_inst_get_key_up()
{
    uint16_t key;
	
	TYPE_FLAG data_type = read_param(&key);
	if(data_type != TYPE_UINT16) 
	{
		KERNEL_PANIC(PANIC_DATA_TYPE_DISCREPANCY);
	}
	
	if(get_key_up(key))
	{
		status_flag |= CARRY_FLAG;
		status_flag &= ~ZERO_FLAG;
	}
	else
	{
		status_flag &= ~CARRY_FLAG;
		status_flag |= ZERO_FLAG;
	}
}

// Check if a key is currently held.
__inline void vm_inst_get_key_held()
{
    uint16_t key;
	
	TYPE_FLAG data_type = read_param(&key);
	if(data_type != TYPE_UINT16) 
	{
		KERNEL_PANIC(PANIC_DATA_TYPE_DISCREPANCY);
	}
	
	if(get_key_held(key))
	{
		status_flag |= CARRY_FLAG;
		status_flag &= ~ZERO_FLAG;
	}
	else
	{
		status_flag &= ~CARRY_FLAG;
		status_flag |= ZERO_FLAG;
	}
}

__inline void vm_inst_sdcard_init()
{
	
}

__inline void vm_inst_sdcard_deinit()
{
	
}

__inline void vm_inst_file_exists()
{
	
}

__inline void vm_inst_dir_exists()
{
	
}

__inline void vm_inst_file_full_read()
{
	
}

__inline void vm_inst_file_read()
{
	
}

__inline void vm_inst_file_append()
{
	
}

__inline void vm_inst_file_write()
{
	
}

__inline void vm_inst_file_rename()
{
	
}

__inline void vm_inst_file_size()
{
	
}

__inline void vm_inst_create_dir()
{
	
}

__inline void vm_inst_delete_file()
{
	
}

__inline void vm_inst_delete_dir()
{
	
}