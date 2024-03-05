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
	
	printf("Assign inst.\n\n");
	
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
	
	printf("Arithmetic calculation inst.\n\n");
	
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

__inline void vm_inst_bitwise()
{
    ++prg_counter;
	
	uint8_t dest_addr_mode, dest_data_type, dest_oper_mode;
	read_attrib(dest_addr_mode, dest_data_type, dest_oper_mode);
	
	ram_t dest_addr;
	read_addr(dest_addr, dest_addr_mode);
	
	mem_buf res;
	uint8_t first_flag = 1;
	
	for(;;)
	{
		uint8_t opr_addr_mode, opr_data_type, opr_oper_mode;
		read_attrib(opr_addr_mode, opr_data_type, opr_oper_mode);
		
		if(opr_data_type == TYPE_TERMINATE) break;
		
		ram_t opr_addr;
		set_read_addr(opr_addr, opr_addr_mode, opr_data_type);
		
		mem_buf opr_data;
		
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
    prg_counter = ram_ptr_addr(prg_counter);
}

__inline void vm_inst_exit()
{
    
}

__inline void vm_inst_set_text_area()
{
    ++prg_counter;
	
	uint8_t src_addr_mode, src_data_type, src_oper_mode;
	ram_t src_addr;
	
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
	
	printf("set_text_area(%d, %d, %d, %d)\n\n", sx, sy, ex, ey);
	
	set_text_area(sx, sy, ex, ey);
}

__inline void vm_inst_set_cursor()
{
    ++prg_counter;
	
	uint8_t src_addr_mode, src_data_type, src_oper_mode;
	ram_t src_addr;
	
	int16_t x, y;

	// Read X position
	read_attrib(src_addr_mode, src_data_type, src_oper_mode);	
	set_read_addr(src_addr, src_addr_mode, src_data_type);
	read_int16(x, src_addr);
	
	// Read Y position
	read_attrib(src_addr_mode, src_data_type, src_oper_mode);
	set_read_addr(src_addr, src_addr_mode, src_data_type);
	read_int16(y, src_addr);
	
	printf("set_cursor(%d, %d)\n\n", x, y);
	
	set_cursor(x, y);
}

__inline void vm_inst_set_text_color()
{
    ++prg_counter;
	
	uint8_t src_addr_mode, src_data_type, src_oper_mode;
	ram_t src_addr;
	
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
	
	printf("set_text_color(%d, %d)\n\n", fg, bg);
	
	set_text_color(fg, bg);
}

__inline void vm_inst_set_text_size()
{
    ++prg_counter;
	
	uint8_t src_addr_mode, src_data_type, src_oper_mode;
	ram_t src_addr;
	
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
	
	printf("set_text_size(%d, %d)\n\n", x, y);
	
	set_text_size(x, y);
}

__inline void vm_inst_set_text_wrap()
{
    ++prg_counter;
	set_text_wrap(1);
}

__inline void vm_inst_clr_text_wrap()
{
    ++prg_counter;
	set_text_wrap(0);
}

__inline void vm_inst_set_font()
{
    ++prg_counter;
	
	uint8_t font;
	read_uint8(font, prg_counter);
	++prg_counter;
	
	set_font(font);
}

__inline void vm_inst_print_chr()
{
    ++prg_counter;
	
	uint8_t src_addr_mode, src_data_type, src_oper_mode;
	read_attrib(src_addr_mode, src_data_type, src_oper_mode);
	
	ram_t src_addr;
	read_addr(src_addr, src_addr_mode);
	
	print_chr(ram_ptr_uint8(src_addr));
}

__inline void vm_inst_print_str()
{
    ++prg_counter;
	
	uint8_t src_addr_mode, src_data_type, src_oper_mode;
	ram_t src_addr;
	
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
	
	printf("print_str(\"%s\")\n\n", &ram[src_addr]);
	
	print_str(&ram[src_addr]);
}

__inline void vm_inst_print_int()
{
    ++prg_counter;
	
	uint8_t src_addr_mode, src_data_type, src_oper_mode;
	read_attrib(src_addr_mode, src_data_type, src_oper_mode);
	
	ram_t src_addr;
	set_read_addr(src_addr, src_addr_mode, src_data_type);
	
	mem_buf tmp;
	
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
	
	printf("print_int(%d)\n\n", tmp.int32);
	
	print_int(tmp.int32);
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

__inline void vm_inst_update_display()
{
    ++prg_counter;
	printf("update_display()\n\n");
	update_display();
}