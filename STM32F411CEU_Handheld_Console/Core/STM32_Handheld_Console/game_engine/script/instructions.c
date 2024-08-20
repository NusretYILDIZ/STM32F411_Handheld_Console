#include "./instructions.h"
#include "./script_engine.h"
#include "../game_engine.h"
#include "../../input/input_driver.h"
#include <math.h>
#include <string.h>

#define __inline  __attribute__((always_inline)) inline

__inline void read_memory(RAM_PTR *addr, void *dest, uint8_t var_type)
{
	switch(var_type)
	{
	case TYPE_NONE:
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
	
	case TYPE_STACK_PTR:
		if(dest) *(STACK_PTR *)dest = stack_ptr;
		break;
	
	case TYPE_DELTA_TIME:
		if(dest) *(float *)dest = 1.0f / (float)delta_time;
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
	
	if(type_flag == TYPE_TERMINATE || type_flag == TYPE_NONE) return type_flag;
	
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
	else if(var_attr & ADDR_ARG)
	{
		uint8_t arg_no = ram[prg_counter];
		prg_counter++;
		
		// If this is an argument, then we are inside a function that we called.
		// This means there is a return address on top of the stack.
		// When searching for an argument, we need to skip that return address.
		RAM_PTR var_addr = (RAM_PTR)stack[stack_ptr - 1 - arg_no];
		read_memory(&var_addr, dest, type_flag);
	}
	else 
	{
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
	else if(var_attr & ADDR_ARG)
	{
		uint8_t arg_no = ram[prg_counter];
		prg_counter++;
		
		if(dest) *dest = (RAM_PTR)(stack[stack_ptr - 1 - arg_no]);
	}
	else 
	{
		KERNEL_PANIC(PANIC_UNKNOWN_ADDR_MODE);
	}
	
	return type_flag;
}

__inline void copy_data(TYPE_FLAG data_type, RAM_PTR dest, MEM_BUF src)
{
	switch(data_type)
	{
	case TYPE_NONE:
		break;
		
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
	
	case TYPE_STACK_PTR:
		stack_ptr = src.stack_ptr;
		break;
	
	case TYPE_STRING:
		while(ram[src.ram_ptr - 1] != '\0')
		{
			*(uint8_t *)(&ram[dest]) = *(uint8_t *)(&ram[src.ram_ptr]);
			dest++;
			src.ram_ptr++;
		}
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

__inline MEM_BUF convert_data_type(TYPE_FLAG dest_type, MEM_BUF src_data, TYPE_FLAG src_type)
{
	MEM_BUF mem_buf;
	
	switch(dest_type)  // There it is, a horrible solution for an average problem.
	{
	case TYPE_FLOAT:
		switch(src_type)
		{
		case TYPE_FLOAT:
			mem_buf.flt = (float)(src_data.flt);
			break;
		
		case TYPE_INT32:
			mem_buf.flt = (float)(src_data.int32);
			break;
		
		case TYPE_UINT32:
			mem_buf.flt = (float)(src_data.uint32);
			break;
		
		case TYPE_INT16:
			mem_buf.flt = (float)(src_data.int16);
			break;
		
		case TYPE_UINT16:
			mem_buf.flt = (float)(src_data.uint16);
			break;
		
		case TYPE_INT8:
			mem_buf.flt = (float)(src_data.int8);
			break;
		
		case TYPE_UINT8:
			mem_buf.flt = (float)(src_data.uint8);
			break;
		
		default:
			KERNEL_PANIC(PANIC_UNKNOWN_DATA_TYPE);
			break;
		}
		break;
	
	case TYPE_INT32:
		switch(src_type)
		{
		case TYPE_FLOAT:
			mem_buf.int32 = (int32_t)(src_data.flt);
			break;
		
		case TYPE_INT32:
			mem_buf.int32 = (int32_t)(src_data.int32);
			break;
		
		case TYPE_UINT32:
			mem_buf.int32 = (int32_t)(src_data.uint32);
			break;
		
		case TYPE_INT16:
			mem_buf.int32 = (int32_t)(src_data.int16);
			break;
		
		case TYPE_UINT16:
			mem_buf.int32 = (int32_t)(src_data.uint16);
			break;
		
		case TYPE_INT8:
			mem_buf.int32 = (int32_t)(src_data.int8);
			break;
		
		case TYPE_UINT8:
			mem_buf.int32 = (int32_t)(src_data.uint8);
			break;
		
		default:
			KERNEL_PANIC(PANIC_UNKNOWN_DATA_TYPE);
			break;
		}
		break;
	
	case TYPE_UINT32:
		switch(src_type)
		{
		case TYPE_FLOAT:
			mem_buf.uint32 = (uint32_t)(src_data.flt);
			break;
		
		case TYPE_INT32:
			mem_buf.uint32 = (uint32_t)(src_data.int32);
			break;
		
		case TYPE_UINT32:
			mem_buf.uint32 = (uint32_t)(src_data.uint32);
			break;
		
		case TYPE_INT16:
			mem_buf.uint32 = (uint32_t)(src_data.int16);
			break;
		
		case TYPE_UINT16:
			mem_buf.uint32 = (uint32_t)(src_data.uint16);
			break;
		
		case TYPE_INT8:
			mem_buf.uint32 = (uint32_t)(src_data.int8);
			break;
		
		case TYPE_UINT8:
			mem_buf.uint32 = (uint32_t)(src_data.uint8);
			break;
		
		default:
			KERNEL_PANIC(PANIC_UNKNOWN_DATA_TYPE);
			break;
		}
		break;
	
	case TYPE_INT16:
		switch(src_type)
		{
		case TYPE_FLOAT:
			mem_buf.int16 = (int16_t)(src_data.flt);
			break;
		
		case TYPE_INT32:
			mem_buf.int16 = (int16_t)(src_data.int32);
			break;
		
		case TYPE_UINT32:
			mem_buf.int16 = (int16_t)(src_data.uint32);
			break;
		
		case TYPE_INT16:
			mem_buf.int16 = (int16_t)(src_data.int16);
			break;
		
		case TYPE_UINT16:
			mem_buf.int16 = (int16_t)(src_data.uint16);
			break;
		
		case TYPE_INT8:
			mem_buf.int16 = (int16_t)(src_data.int8);
			break;
		
		case TYPE_UINT8:
			mem_buf.int16 = (int16_t)(src_data.uint8);
			break;
		
		default:
			KERNEL_PANIC(PANIC_UNKNOWN_DATA_TYPE);
			break;
		}
		break;
	
	case TYPE_UINT16:
		switch(src_type)
		{
		case TYPE_FLOAT:
			mem_buf.uint16 = (uint16_t)(src_data.flt);
			break;
		
		case TYPE_INT32:
			mem_buf.uint16 = (uint16_t)(src_data.int32);
			break;
		
		case TYPE_UINT32:
			mem_buf.uint16 = (uint16_t)(src_data.uint32);
			break;
		
		case TYPE_INT16:
			mem_buf.uint16 = (uint16_t)(src_data.int16);
			break;
		
		case TYPE_UINT16:
			mem_buf.uint16 = (uint16_t)(src_data.uint16);
			break;
		
		case TYPE_INT8:
			mem_buf.uint16 = (uint16_t)(src_data.int8);
			break;
		
		case TYPE_UINT8:
			mem_buf.uint16 = (uint16_t)(src_data.uint8);
			break;
		
		default:
			KERNEL_PANIC(PANIC_UNKNOWN_DATA_TYPE);
			break;
		}
		break;
	
	case TYPE_INT8:
		switch(src_type)
		{
		case TYPE_FLOAT:
			mem_buf.int8 = (int8_t)(src_data.flt);
			break;
		
		case TYPE_INT32:
			mem_buf.int8 = (int8_t)(src_data.int32);
			break;
		
		case TYPE_UINT32:
			mem_buf.int8 = (int8_t)(src_data.uint32);
			break;
		
		case TYPE_INT16:
			mem_buf.int8 = (int8_t)(src_data.int16);
			break;
		
		case TYPE_UINT16:
			mem_buf.int8 = (int8_t)(src_data.uint16);
			break;
		
		case TYPE_INT8:
			mem_buf.int8 = (int8_t)(src_data.int8);
			break;
		
		case TYPE_UINT8:
			mem_buf.int8 = (int8_t)(src_data.uint8);
			break;
		
		default:
			KERNEL_PANIC(PANIC_UNKNOWN_DATA_TYPE);
			break;
		}
		break;
	
	case TYPE_UINT8:
		switch(src_type)
		{
		case TYPE_FLOAT:
			mem_buf.uint8 = (uint8_t)(src_data.flt);
			break;
		
		case TYPE_INT32:
			mem_buf.uint8 = (uint8_t)(src_data.int32);
			break;
		
		case TYPE_UINT32:
			mem_buf.uint8 = (uint8_t)(src_data.uint32);
			break;
		
		case TYPE_INT16:
			mem_buf.uint8 = (uint8_t)(src_data.int16);
			break;
		
		case TYPE_UINT16:
			mem_buf.uint8 = (uint8_t)(src_data.uint16);
			break;
		
		case TYPE_INT8:
			mem_buf.uint8 = (uint8_t)(src_data.int8);
			break;
		
		case TYPE_UINT8:
			mem_buf.uint8 = (uint8_t)(src_data.uint8);
			break;
		
		default:
			KERNEL_PANIC(PANIC_UNKNOWN_DATA_TYPE);
			break;
		}
		break;
	
	default:
		KERNEL_PANIC(PANIC_UNKNOWN_DATA_TYPE);
		break;
	}
	
	return mem_buf;
}

__inline RPN_DATA read_rpn_data()
{
	RPN_DATA rpn_data; // = *(RPN_DATA *)(&ram[prg_counter]);
	memcpy(&rpn_data, &ram[prg_counter], sizeof(RPN_DATA));
	prg_counter += sizeof(RPN_DATA);
	
	if(rpn_data.type == RPN_TYPE_NUMERAL)  // Get the absolute values so we won't have to deal with addresses.
	{
		if((rpn_data.attr & ADDR_MASK) == ADDR_ABS)
		{
			RAM_PTR var_addr = rpn_data.value.ram_ptr;
			read_memory(&var_addr, (void *)(&rpn_data.value), rpn_data.attr & TYPE_MASK);
		}
		else if((rpn_data.attr & ADDR_MASK) == ADDR_PTR)
		{
			RAM_PTR var_addr = rpn_data.value.ram_ptr;
			var_addr = *(RAM_PTR *)(&ram[var_addr]);
			
			read_memory(&var_addr, (void *)(&rpn_data.value), rpn_data.attr & TYPE_MASK);
		}
		else if((rpn_data.attr & ADDR_MASK) != ADDR_IMM)
		{
			KERNEL_PANIC(PANIC_RPN_SOLVER_UNKNOWN_ADDR_MODE);
			rpn_data.type = RPN_TYPE_ERROR;
		}
	}
	
	return rpn_data;
}

__inline RPN_STACK_DATA get_rpn_solver_data(RPN_DATA rpn_data)
{
	if(rpn_data.type != RPN_TYPE_NUMERAL) 
	{
		RPN_STACK_DATA error = {
			.type = RPNS_TYPE_ERROR,
			0
		};
		return error;
	}
	
	RPN_STACK_DATA solver_data;
	
	switch(rpn_data.attr & TYPE_MASK)
	{
	case TYPE_FLOAT:
		solver_data.type = RPNS_TYPE_FLOAT;
		solver_data.value.float32 = rpn_data.value.flt;
		break;
	
	case TYPE_INT32:
		solver_data.type = RPNS_TYPE_INT64;
		solver_data.value.int64 = (int64_t)(rpn_data.value.int32);
		break;
	
	case TYPE_UINT32:
		solver_data.type = RPNS_TYPE_INT64;
		solver_data.value.int64 = (int64_t)(rpn_data.value.uint32);
		break;
	
	case TYPE_INT16:
		solver_data.type = RPNS_TYPE_INT64;
		solver_data.value.int64 = (int64_t)(rpn_data.value.int16);
		break;
	
	case TYPE_UINT16:
		solver_data.type = RPNS_TYPE_INT64;
		solver_data.value.int64 = (int64_t)(rpn_data.value.uint16);
		break;
	
	case TYPE_INT8:
		solver_data.type = RPNS_TYPE_INT64;
		solver_data.value.int64 = (int64_t)(rpn_data.value.int8);
		break;
	
	case TYPE_UINT8:
		solver_data.type = RPNS_TYPE_INT64;
		solver_data.value.int64 = (int64_t)(rpn_data.value.uint8);
		break;
	
	default:
		solver_data.type = RPNS_TYPE_ERROR;
		break;
	}
	
	return solver_data;
}

__inline void push_rpn_stack(RPN_STACK_DATA rpn_data)
{
	if(rpn_stack_ptr >= RPN_STACK_SIZE)
	{
		KERNEL_PANIC(PANIC_RPN_STACK_OVERFLOW);
		return;
	}
	
	rpn_stack[rpn_stack_ptr] = rpn_data;
	rpn_stack_ptr++;
}

__inline RPN_STACK_DATA pop_rpn_stack()
{
	if(rpn_stack_ptr <= 0)
	{
		KERNEL_PANIC(PANIC_RPN_STACK_UNDERFLOW);
		
		RPN_STACK_DATA error = {
			.type = RPN_TYPE_ERROR,
			0,
		};
		return error;
	}
	
	rpn_stack_ptr--;
	return rpn_stack[rpn_stack_ptr];
}

#define is_zero_float(num)          ((num) < 0.00001f && (num) > -0.00001f)
#define is_equal_float(num1, num2)  (((num1) - (num2)) < 0.00001f && ((num1) - (num2)) > -0.00001f)

__inline void calculate_rpn(RPN_STACK_DATA num1, RPN_STACK_DATA num2, RPN_TYPE operator)
{
	RPN_STACK_DATA result = { 0 };
	
	switch(operator)
	{
	// Operators that have one argument
	case RPN_TYPE_MINUS:
		if(num1.type == RPNS_TYPE_INT64) 
		{
			result.value.int64 = -num1.value.int64;
			result.type = RPNS_TYPE_INT64;
		}
		else if(num1.type == RPNS_TYPE_FLOAT) 
		{
			result.value.float32 = -num1.value.float32;
			result.type = RPNS_TYPE_FLOAT;
		}
		else
		{
			KERNEL_PANIC(PANIC_RPN_SOLVER_UNKNOWN_TYPE);
			return;
		}
		break;
	
	case RPN_TYPE_BITWISE_NOT:
		if(num1.type == RPNS_TYPE_INT64)
		{
			result.value.int64 = ~num1.value.int64;
			result.type = RPNS_TYPE_INT64;
		}
		else
		{
			KERNEL_PANIC(PANIC_RPN_SOLVER_UNKNOWN_TYPE);
			return;
		}
		break;
	
	case RPN_TYPE_LOGICAL_NOT:
		if(num1.type == RPNS_TYPE_INT64 || num1.type == RPNS_TYPE_FLOAT) 
		{
			result.value.int64 = !num1.value.int64;
			result.type = RPNS_TYPE_INT64;
		}
		else
		{
			KERNEL_PANIC(PANIC_RPN_SOLVER_UNKNOWN_TYPE);
			return;
		}
		break;
	
	// Operator that have two arguments
	// Arithmetic operators
	case RPN_TYPE_ADD:
		if(num1.type == RPNS_TYPE_INT64 && num2.type == RPNS_TYPE_INT64)
		{
			result.value.int64 = num1.value.int64 + num2.value.int64;
			result.type = RPNS_TYPE_INT64;
		}
		else if(num1.type == RPNS_TYPE_FLOAT && num2.type == RPNS_TYPE_FLOAT)
		{
			result.value.float32 = num1.value.float32 + num2.value.float32;
			result.type = RPNS_TYPE_FLOAT;
		}
		else if(num1.type == RPNS_TYPE_FLOAT && num2.type == RPNS_TYPE_INT64)
		{
			result.value.float32 = num1.value.float32 + (float)(num2.value.int64);
			result.type = RPNS_TYPE_FLOAT;
		}
		else if(num1.type == RPNS_TYPE_INT64 && num2.type == RPNS_TYPE_FLOAT)
		{
			result.value.float32 = (float)(num1.value.int64) + num2.value.float32;
			result.type = RPNS_TYPE_FLOAT;
		}
		else
		{
			KERNEL_PANIC(PANIC_RPN_SOLVER_UNKNOWN_TYPE);
			return;
		}
		break;
	
	case RPN_TYPE_SUB:
		if(num1.type == RPNS_TYPE_INT64 && num2.type == RPNS_TYPE_INT64)
		{
			result.value.int64 = num1.value.int64 - num2.value.int64;
			result.type = RPNS_TYPE_INT64;
		}
		else if(num1.type == RPNS_TYPE_FLOAT && num2.type == RPNS_TYPE_FLOAT)
		{
			result.value.float32 = num1.value.float32 - num2.value.float32;
			result.type = RPNS_TYPE_FLOAT;
		}
		else if(num1.type == RPNS_TYPE_FLOAT && num2.type == RPNS_TYPE_INT64)
		{
			result.value.float32 = num1.value.float32 - (float)(num2.value.int64);
			result.type = RPNS_TYPE_FLOAT;
		}
		else if(num1.type == RPNS_TYPE_INT64 && num2.type == RPNS_TYPE_FLOAT)
		{
			result.value.float32 = (float)(num1.value.int64) - num2.value.float32;
			result.type = RPNS_TYPE_FLOAT;
		}
		else
		{
			KERNEL_PANIC(PANIC_RPN_SOLVER_UNKNOWN_TYPE);
			return;
		}
		break;
	
	case RPN_TYPE_MUL:
		if(num1.type == RPNS_TYPE_INT64 && num2.type == RPNS_TYPE_INT64)
		{
			result.value.int64 = num1.value.int64 * num2.value.int64;
			result.type = RPNS_TYPE_INT64;
		}
		else if(num1.type == RPNS_TYPE_FLOAT && num2.type == RPNS_TYPE_FLOAT)
		{
			result.value.float32 = num1.value.float32 * num2.value.float32;
			result.type = RPNS_TYPE_FLOAT;
		}
		else if(num1.type == RPNS_TYPE_FLOAT && num2.type == RPNS_TYPE_INT64)
		{
			result.value.float32 = num1.value.float32 * (float)(num2.value.int64);
			result.type = RPNS_TYPE_FLOAT;
		}
		else if(num1.type == RPNS_TYPE_INT64 && num2.type == RPNS_TYPE_FLOAT)
		{
			result.value.float32 = (float)(num1.value.int64) * num2.value.float32;
			result.type = RPNS_TYPE_FLOAT;
		}
		else
		{
			KERNEL_PANIC(PANIC_RPN_SOLVER_UNKNOWN_TYPE);
			return;
		}
		break;
	
	case RPN_TYPE_DIV:
		if(num1.type == RPNS_TYPE_INT64 && num2.type == RPNS_TYPE_INT64)
		{
			if(num2.value.int64 == 0)
			{
				KERNEL_PANIC(PANIC_RPN_SOLVER_DIVIDE_BY_ZERO);
				return;
			}
			else
			{
				result.value.int64 = num1.value.int64 / num2.value.int64;
				result.type = RPNS_TYPE_INT64;
			}
		}
		else if(num1.type == RPNS_TYPE_FLOAT && num2.type == RPNS_TYPE_FLOAT)
		{
			if(is_zero_float(num2.value.float32))
			{
				KERNEL_PANIC(PANIC_RPN_SOLVER_DIVIDE_BY_ZERO);
				return;
			}
			else
			{
				result.value.float32 = num1.value.float32 / num2.value.float32;
				result.type = RPNS_TYPE_FLOAT;
			}
		}
		else if(num1.type == RPNS_TYPE_FLOAT && num2.type == RPNS_TYPE_INT64)
		{
			if(num2.value.int64 == 0)
			{
				KERNEL_PANIC(PANIC_RPN_SOLVER_DIVIDE_BY_ZERO);
				return;
			}
			else
			{
				result.value.float32 = num1.value.float32 / (float)(num2.value.int64);
				result.type = RPNS_TYPE_FLOAT;
			}
		}
		else if(num1.type == RPNS_TYPE_INT64 && num2.type == RPNS_TYPE_FLOAT)
		{
			if(is_zero_float(num2.value.float32))
			{
				KERNEL_PANIC(PANIC_RPN_SOLVER_DIVIDE_BY_ZERO);
				return;
			}
			else
			{
				result.value.float32 = (float)(num1.value.int64) / num2.value.float32;
				result.type = RPNS_TYPE_FLOAT;
			}
		}
		else
		{
			KERNEL_PANIC(PANIC_RPN_SOLVER_UNKNOWN_TYPE);
			return;
		}
		break;
	
	case RPN_TYPE_MOD:
		if(num1.type == RPNS_TYPE_INT64 && num2.type == RPNS_TYPE_INT64)
		{
			result.value.int64 = num1.value.int64 % num2.value.int64;
			result.type = RPNS_TYPE_INT64;
		}
		else
		{
			KERNEL_PANIC(PANIC_RPN_SOLVER_UNKNOWN_TYPE);
			return;
		}
		break;
	
	// Bitwise operators
	case RPN_TYPE_BITWISE_AND:
		if(num1.type == RPNS_TYPE_INT64 && num2.type == RPNS_TYPE_INT64)
		{
			result.value.int64 = num1.value.int64 & num2.value.int64;
			result.type = RPNS_TYPE_INT64;
		}
		else
		{
			KERNEL_PANIC(PANIC_RPN_SOLVER_UNKNOWN_TYPE);
			return;
		}
		break;
	
	case RPN_TYPE_BITWISE_OR:
		if(num1.type == RPNS_TYPE_INT64 && num2.type == RPNS_TYPE_INT64)
		{
			result.value.int64 = num1.value.int64 | num2.value.int64;
			result.type = RPNS_TYPE_INT64;
		}
		else
		{
			KERNEL_PANIC(PANIC_RPN_SOLVER_UNKNOWN_TYPE);
			return;
		}
		break;
	
	case RPN_TYPE_BITWISE_XOR:
		if(num1.type == RPNS_TYPE_INT64 && num2.type == RPNS_TYPE_INT64)
		{
			result.value.int64 = num1.value.int64 ^ num2.value.int64;
			result.type = RPNS_TYPE_INT64;
		}
		else
		{
			KERNEL_PANIC(PANIC_RPN_SOLVER_UNKNOWN_TYPE);
			return;
		}
		break;
	
	case RPN_TYPE_BITSHIFT_LEFT:
		if(num1.type == RPNS_TYPE_INT64 && num2.type == RPNS_TYPE_INT64)
		{
			result.value.int64 = num1.value.int64 << num2.value.int64;
			result.type = RPNS_TYPE_INT64;
		}
		else
		{
			KERNEL_PANIC(PANIC_RPN_SOLVER_UNKNOWN_TYPE);
			return;
		}
		break;
	
	case RPN_TYPE_BITSHIFT_RIGHT:
		if(num1.type == RPNS_TYPE_INT64 && num2.type == RPNS_TYPE_INT64)
		{
			result.value.int64 = num1.value.int64 >> num2.value.int64;
			result.type = RPNS_TYPE_INT64;
		}
		else
		{
			KERNEL_PANIC(PANIC_RPN_SOLVER_UNKNOWN_TYPE);
			return;
		}
		break;
	
	// Comparison operators
	case RPN_TYPE_EQUAL:
		if(num1.type == RPNS_TYPE_INT64 && num2.type == RPNS_TYPE_INT64)
		{
			result.value.int64 = num1.value.int64 == num2.value.int64;
			result.type = RPNS_TYPE_INT64;
		}
		else if(num1.type == RPNS_TYPE_FLOAT && num2.type == RPNS_TYPE_FLOAT)
		{
			result.value.int64 = is_equal_float(num1.value.float32, num2.value.float32);
			result.type = RPNS_TYPE_INT64;
		}
		else if(num1.type == RPNS_TYPE_FLOAT && num2.type == RPNS_TYPE_INT64)
		{
			result.value.int64 = is_equal_float(num1.value.float32, (float)(num2.value.int64));
			result.type = RPNS_TYPE_INT64;
		}
		else if(num1.type == RPNS_TYPE_INT64 && num2.type == RPNS_TYPE_FLOAT)
		{
			result.value.int64 = is_equal_float((float)(num1.value.int64), num2.value.float32);
			result.type = RPNS_TYPE_INT64;
		}
		else
		{
			KERNEL_PANIC(PANIC_RPN_SOLVER_UNKNOWN_TYPE);
			return;
		}
		break;
	
	case RPN_TYPE_NOT_EQUAL:
		if(num1.type == RPNS_TYPE_INT64 && num2.type == RPNS_TYPE_INT64)
		{
			result.value.int64 = num1.value.int64 != num2.value.int64;
			result.type = RPNS_TYPE_INT64;
		}
		else if(num1.type == RPNS_TYPE_FLOAT && num2.type == RPNS_TYPE_FLOAT)
		{
			result.value.int64 = !is_equal_float(num1.value.float32, num2.value.float32);
			result.type = RPNS_TYPE_INT64;
		}
		else if(num1.type == RPNS_TYPE_FLOAT && num2.type == RPNS_TYPE_INT64)
		{
			result.value.int64 = !is_equal_float(num1.value.float32, (float)(num2.value.int64));
			result.type = RPNS_TYPE_INT64;
		}
		else if(num1.type == RPNS_TYPE_INT64 && num2.type == RPNS_TYPE_FLOAT)
		{
			result.value.int64 = !is_equal_float((float)(num1.value.int64), num2.value.float32);
			result.type = RPNS_TYPE_INT64;
		}
		else
		{
			KERNEL_PANIC(PANIC_RPN_SOLVER_UNKNOWN_TYPE);
			return;
		}
		break;
	
	case RPN_TYPE_LESS:
		if(num1.type == RPNS_TYPE_INT64 && num2.type == RPNS_TYPE_INT64)
		{
			result.value.int64 = num1.value.int64 < num2.value.int64;
			result.type = RPNS_TYPE_INT64;
		}
		else if(num1.type == RPNS_TYPE_FLOAT && num2.type == RPNS_TYPE_FLOAT)
		{
			result.value.int64 = num1.value.float32 < num2.value.float32;
			result.type = RPNS_TYPE_INT64;
		}
		else if(num1.type == RPNS_TYPE_FLOAT && num2.type == RPNS_TYPE_INT64)
		{
			result.value.int64 = num1.value.float32 < (float)(num2.value.int64);
			result.type = RPNS_TYPE_INT64;
		}
		else if(num1.type == RPNS_TYPE_INT64 && num2.type == RPNS_TYPE_FLOAT)
		{
			result.value.int64 = (float)(num1.value.int64) < num2.value.float32;
			result.type = RPNS_TYPE_INT64;
		}
		else
		{
			KERNEL_PANIC(PANIC_RPN_SOLVER_UNKNOWN_TYPE);
			return;
		}
		break;
	
	case RPN_TYPE_GREATER:
		if(num1.type == RPNS_TYPE_INT64 && num2.type == RPNS_TYPE_INT64)
		{
			result.value.int64 = num1.value.int64 > num2.value.int64;
			result.type = RPNS_TYPE_INT64;
		}
		else if(num1.type == RPNS_TYPE_FLOAT && num2.type == RPNS_TYPE_FLOAT)
		{
			result.value.int64 = num1.value.float32 > num2.value.float32;
			result.type = RPNS_TYPE_INT64;
		}
		else if(num1.type == RPNS_TYPE_FLOAT && num2.type == RPNS_TYPE_INT64)
		{
			result.value.int64 = num1.value.float32 > (float)(num2.value.int64);
			result.type = RPNS_TYPE_INT64;
		}
		else if(num1.type == RPNS_TYPE_INT64 && num2.type == RPNS_TYPE_FLOAT)
		{
			result.value.int64 = (float)(num1.value.int64) > num2.value.float32;
			result.type = RPNS_TYPE_INT64;
		}
		else
		{
			KERNEL_PANIC(PANIC_RPN_SOLVER_UNKNOWN_TYPE);
			return;
		}
		break;
	
	case RPN_TYPE_LESS_EQUAL:
		if(num1.type == RPNS_TYPE_INT64 && num2.type == RPNS_TYPE_INT64)
		{
			result.value.int64 = num1.value.int64 <= num2.value.int64;
			result.type = RPNS_TYPE_INT64;
		}
		else if(num1.type == RPNS_TYPE_FLOAT && num2.type == RPNS_TYPE_FLOAT)
		{
			result.value.int64 = num1.value.float32 <= num2.value.float32;
			result.type = RPNS_TYPE_INT64;
		}
		else if(num1.type == RPNS_TYPE_FLOAT && num2.type == RPNS_TYPE_INT64)
		{
			result.value.int64 = num1.value.float32 <= (float)(num2.value.int64);
			result.type = RPNS_TYPE_INT64;
		}
		else if(num1.type == RPNS_TYPE_INT64 && num2.type == RPNS_TYPE_FLOAT)
		{
			result.value.int64 = (float)(num1.value.int64) <= num2.value.float32;
			result.type = RPNS_TYPE_INT64;
		}
		else
		{
			KERNEL_PANIC(PANIC_RPN_SOLVER_UNKNOWN_TYPE);
			return;
		}
		break;
	
	case RPN_TYPE_GREATER_EQUAL:
		if(num1.type == RPNS_TYPE_INT64 && num2.type == RPNS_TYPE_INT64)
		{
			result.value.int64 = num1.value.int64 >= num2.value.int64;
			result.type = RPNS_TYPE_INT64;
		}
		else if(num1.type == RPNS_TYPE_FLOAT && num2.type == RPNS_TYPE_FLOAT)
		{
			result.value.int64 = num1.value.float32 >= num2.value.float32;
			result.type = RPNS_TYPE_INT64;
		}
		else if(num1.type == RPNS_TYPE_FLOAT && num2.type == RPNS_TYPE_INT64)
		{
			result.value.int64 = num1.value.float32 >= (float)(num2.value.int64);
			result.type = RPNS_TYPE_INT64;
		}
		else if(num1.type == RPNS_TYPE_INT64 && num2.type == RPNS_TYPE_FLOAT)
		{
			result.value.int64 = (float)(num1.value.int64) >= num2.value.float32;
			result.type = RPNS_TYPE_INT64;
		}
		else
		{
			KERNEL_PANIC(PANIC_RPN_SOLVER_UNKNOWN_TYPE);
			return;
		}
		break;
	
	// Logical operators
	case RPN_TYPE_LOGICAL_AND:
		if((num1.type == RPNS_TYPE_INT64 || num1.type == RPNS_TYPE_FLOAT) && (num2.type == RPNS_TYPE_INT64 || num2.type == RPNS_TYPE_FLOAT))
		{
			result.value.int64 = num1.value.int64 && num2.value.int64;
			result.type = RPNS_TYPE_INT64;
		}
		else
		{
			KERNEL_PANIC(PANIC_RPN_SOLVER_UNKNOWN_TYPE);
			return;
		}
		break;
	
	case RPN_TYPE_LOGICAL_OR:
		if((num1.type == RPNS_TYPE_INT64 || num1.type == RPNS_TYPE_FLOAT) && (num2.type == RPNS_TYPE_INT64 || num2.type == RPNS_TYPE_FLOAT))
		{
			result.value.int64 = num1.value.int64 || num2.value.int64;
			result.type = RPNS_TYPE_INT64;
		}
		else
		{
			KERNEL_PANIC(PANIC_RPN_SOLVER_UNKNOWN_TYPE);
			return;
		}
		break;
	
	default:
		KERNEL_PANIC(PANIC_RPN_SOLVER_UNKNOWN_OPERATOR);
		return;
	}
	
	push_rpn_stack(result);
}

#define is_rpn_stack_empty()  (rpn_stack_ptr == 0)

__inline RPN_STACK_DATA solve_rpn()
{
	RPN_DATA rpn_data = { 0 };
	
	while(rpn_data.type != RPN_TYPE_TERMINATE)
	{
		rpn_data = read_rpn_data();
		
		if(rpn_data.type == RPN_TYPE_NONE) continue;
		if(rpn_data.type == RPN_TYPE_ERROR || rpn_data.type == RPN_TYPE_TERMINATE) break;
		
		if(rpn_data.type == RPN_TYPE_NUMERAL) push_rpn_stack(get_rpn_solver_data(rpn_data));
		else
		{
			if(rpn_data.type == RPN_TYPE_MINUS || 
			   rpn_data.type == RPN_TYPE_BITWISE_NOT || 
			   rpn_data.type == RPN_TYPE_LOGICAL_NOT)
			{
				RPN_STACK_DATA num2 = { 0 };
				RPN_STACK_DATA num1 = pop_rpn_stack();
				
				calculate_rpn(num1, num2, rpn_data.type);
			}
			else
			{
				RPN_STACK_DATA num2 = pop_rpn_stack();
				RPN_STACK_DATA num1 = pop_rpn_stack();
				
				calculate_rpn(num1, num2, rpn_data.type);
			}
		}
	}
	
	RPN_STACK_DATA result = pop_rpn_stack();

	if(!is_rpn_stack_empty())
	{
		KERNEL_PANIC(PANIC_RPN_SOLVER_TOO_MANY_RESULTS);
		result.type = RPNS_TYPE_ERROR;
	}
	
	return result;
}

__inline void vm_inst_evaluate_rpn()
{
	rpn_stack_ptr = 0;
	
	RAM_PTR dest_addr;
	TYPE_FLAG dest_type = read_addr(&dest_addr);
	
	RPN_STACK_DATA result = solve_rpn();
	
	if(status_flag & KERNEL_PANIC_FLAG || result.type == RPNS_TYPE_ERROR) return;
	
	if(result.type == RPNS_TYPE_INT64)
	{
		if(result.value.int64 == 0)
		{
			status_flag |= ZERO_FLAG;
			status_flag &= ~SIGN_FLAG;
		}
		else status_flag &= ~ZERO_FLAG;
		
		if(result.value.int64 < 0)
		{
			status_flag |= SIGN_FLAG;
			status_flag &= ~ZERO_FLAG;
		}
		else status_flag &= ~SIGN_FLAG;
	}
	else if(result.type == RPNS_TYPE_FLOAT)
	{
		if(is_zero_float(result.value.float32))
		{
			status_flag |= ZERO_FLAG;
			status_flag &= ~SIGN_FLAG;
		}
		else status_flag &= ~ZERO_FLAG;
		
		if(result.value.float32 < 0.0f && !is_zero_float(result.value.float32))
		{
			status_flag |= SIGN_FLAG;
			status_flag &= ~ZERO_FLAG;
		}
		else status_flag &= ~SIGN_FLAG;
	}
	
	switch(dest_type)  // Write the result to destination
	{
	case TYPE_FLOAT:
		if(result.type == RPNS_TYPE_INT64) 
			*(float *)(&ram[dest_addr]) = (float)(result.value.int64);
		else if(result.type == RPNS_TYPE_FLOAT) 
			*(float *)(&ram[dest_addr]) = result.value.float32;
		else
		{
			KERNEL_PANIC(PANIC_RPN_SOLVER_UNKNOWN_TYPE);
		}
		break;
	
	case TYPE_INT32:
		if(result.type == RPNS_TYPE_INT64) 
			*(int32_t *)(&ram[dest_addr]) = (int32_t)(result.value.int64);
		else if(result.type == RPNS_TYPE_FLOAT) 
			*(int32_t *)(&ram[dest_addr]) = (int32_t)(result.value.float32);
		else
		{
			KERNEL_PANIC(PANIC_RPN_SOLVER_UNKNOWN_TYPE);
		}
		break;
	
	case TYPE_UINT32:
		if(result.type == RPNS_TYPE_INT64) 
			*(uint32_t *)(&ram[dest_addr]) = (uint32_t)(result.value.int64);
		else if(result.type == RPNS_TYPE_FLOAT) 
			*(uint32_t *)(&ram[dest_addr]) = (uint32_t)(result.value.float32);
		else
		{
			KERNEL_PANIC(PANIC_RPN_SOLVER_UNKNOWN_TYPE);
		}
		break;
	
	case TYPE_INT16:
		if(result.type == RPNS_TYPE_INT64) 
			*(int16_t *)(&ram[dest_addr]) = (int16_t)(result.value.int64);
		else if(result.type == RPNS_TYPE_FLOAT) 
			*(int16_t *)(&ram[dest_addr]) = (int16_t)(result.value.float32);
		else
		{
			KERNEL_PANIC(PANIC_RPN_SOLVER_UNKNOWN_TYPE);
		}
		break;
	
	case TYPE_UINT16:
		if(result.type == RPNS_TYPE_INT64) 
			*(uint16_t *)(&ram[dest_addr]) = (uint16_t)(result.value.int64);
		else if(result.type == RPNS_TYPE_FLOAT) 
			*(uint16_t *)(&ram[dest_addr]) = (uint16_t)(result.value.float32);
		else
		{
			KERNEL_PANIC(PANIC_RPN_SOLVER_UNKNOWN_TYPE);
		}
		break;
	
	case TYPE_INT8:
		if(result.type == RPNS_TYPE_INT64) 
			*(int8_t *)(&ram[dest_addr]) = (int8_t)(result.value.int64);
		else if(result.type == RPNS_TYPE_FLOAT) 
			*(int8_t *)(&ram[dest_addr]) = (int8_t)(result.value.float32);
		else
		{
			KERNEL_PANIC(PANIC_RPN_SOLVER_UNKNOWN_TYPE);
		}
		break;
	
	case TYPE_UINT8:
		if(result.type == RPNS_TYPE_INT64) 
			*(uint8_t *)(&ram[dest_addr]) = (uint8_t)(result.value.int64);
		else if(result.type == RPNS_TYPE_FLOAT) 
			*(uint8_t *)(&ram[dest_addr]) = (uint8_t)(result.value.float32);
		else
		{
			KERNEL_PANIC(PANIC_RPN_SOLVER_UNKNOWN_TYPE);
		}
		break;
	
	default:
		KERNEL_PANIC(PANIC_UNKNOWN_DATA_TYPE);
		break;
	}
}

#define arg_count_pos()  (sizeof(RAM_PTR) * 8 - 4)

__inline uint32_t get_func_arg()
{
	uint8_t arg_attr = ram[prg_counter];
	prg_counter++;
	
	uint32_t arg;
	
	if(arg_attr & ADDR_IMM)
	{
		read_memory(&prg_counter, &arg, arg_attr & TYPE_MASK);
	}
	else if(arg_attr & ADDR_ABS || arg_attr & ADDR_PTR)
	{
		RAM_PTR arg_addr = *(RAM_PTR *)(&ram[prg_counter]);
		prg_counter += sizeof(RAM_PTR);
		
		read_memory(&arg_addr, &arg, arg_attr & TYPE_MASK);
	}
	else
	{
		KERNEL_PANIC(PANIC_UNKNOWN_ADDR_MODE);
	}
	
	return arg;
}

__inline void vm_inst_call_no_arg()
{
	RAM_PTR func_addr;
	read_addr(&func_addr);
	
	// 4 most significant bits will be used as argument count for that function (therefore a function can take up to 15 arguments).
	// Since that function doesn't take any arguments, we zero out these bits so argument count becomes zero.
	// Also size of RAM_PTR is determined according to RAM size, so we need to calculate the position of these bits.
	func_addr &= ~(15 << arg_count_pos());
	
	vm_push_stack((uint32_t)(prg_counter));
	prg_counter = func_addr;
}

__inline void vm_inst_call_with_arg()
{
	RAM_PTR func_addr;
	read_addr(&func_addr);
	
	unsigned int arg_count = func_addr >> arg_count_pos();
	
	for(unsigned int i = 0; i < arg_count; i++)
	{
		vm_push_stack(get_func_arg());
	}
	
	// We also need to clear the argument count bits to get the correct jump address.
	func_addr &= ~(15 << arg_count_pos());
	
	vm_push_stack((uint32_t)(prg_counter));
	prg_counter = func_addr;
}

__inline void vm_inst_return()
{
	RAM_PTR return_addr = (RAM_PTR)vm_pop_stack();
	unsigned int arg_count = return_addr >> arg_count_pos();
	
	for(; arg_count > 0; arg_count--)
	{
		(void)vm_pop_stack();  // Clear leftovers.
	}
	
	return_addr &= ~(15 << arg_count_pos());
	prg_counter = return_addr;
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
	update_display();
}

// Notify game engine that we reached end of game logic loop, so it can do other stuff and start over.
__inline void vm_inst_end_of_loop()
{
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