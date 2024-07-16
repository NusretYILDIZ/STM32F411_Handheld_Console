#include "./instructions.h"
#include "./script_engine.h"
#include "./mem_access_def.h"
#include <math.h>
#include <string.h>

#define __inline  __attribute__((always_inline)) inline 

__inline void vm_inst_syscall()
{
    
}

__inline void vm_inst_assign()
{
	++prg_counter;
	
	//printf("Assign inst.\n\n");
	
	uint8_t dest_addr_mode, dest_data_type, oper_mode;
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
	}
}

__inline void vm_inst_arith_calc()
{
	++prg_counter;
	
	//printf("Arithmetic calculation inst.\n\n");
	
	uint8_t dest_addr_mode, dest_data_type, dest_oper_mode;
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
	}
}

__inline void vm_inst_bitwise()
{
    ++prg_counter;
	
	uint8_t dest_addr_mode, dest_data_type, dest_oper_mode;
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
	}
}

__inline void vm_inst_logical()
{
    ++prg_counter;
	
	uint8_t dest_addr_mode, dest_data_type, dest_oper_mode;
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
	else    logical_flag |=  ZERO_FLAG;
}

__inline void vm_inst_jsr()
{
    ++prg_counter;
    
    RAM_PTR jmp_addr = *(RAM_PTR *) (&ram[prg_counter]);
    prg_counter += sizeof(RAM_PTR);
    
    vm_push(prg_counter);
    prg_counter = jmp_addr;
}

__inline void vm_inst_rts()
{
    prg_counter = (RAM_PTR) vm_pop();
}

__inline void vm_inst_jump_if()
{
    ++prg_counter;
    
    if(logical_flag)
        prg_counter = *(RAM_PTR *) (&ram[prg_counter]);
    else
        prg_counter += sizeof(RAM_PTR);
}

__inline void vm_inst_jump()
{
    ++prg_counter;
    prg_counter = ram_ptr_addr(prg_counter);
}

// Exit from program and return to system menu.
__inline void vm_inst_exit()
{
    
}

__inline void vm_inst_set_text_area()
{
    ++prg_counter;
	
	uint8_t src_addr_mode, src_data_type, src_oper_mode;
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
	
	set_text_area(sx, sy, ex, ey);
}

__inline void vm_inst_set_cursor()
{
    ++prg_counter;
	
	uint8_t src_addr_mode, src_data_type, src_oper_mode;
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
	
	set_cursor(x, y);
}

__inline void vm_inst_set_text_color()
{
    ++prg_counter;
	
	uint8_t src_addr_mode, src_data_type, src_oper_mode;
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
	
	set_text_color(fg, bg);
}

__inline void vm_inst_set_text_size()
{
    ++prg_counter;
	
	uint8_t src_addr_mode, src_data_type, src_oper_mode;
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
	
	set_text_size(x, y);
}

// The text that doesn't fit in text area now pushed into next line.
__inline void vm_inst_set_text_wrap()
{
    ++prg_counter;
	set_text_wrap(1);
}

// The text that doesn't fit in text area is now clipped.
__inline void vm_inst_clr_text_wrap()
{
    ++prg_counter;
	set_text_wrap(0);
}

// Set font of text for printing into VRAM.
__inline void vm_inst_set_font()
{
    ++prg_counter;
	
	uint8_t font;
	read_uint8(font, prg_counter);
	++prg_counter;
	
	set_font(font);
}

// Print a single character into VRAM.
__inline void vm_inst_print_chr()
{
    ++prg_counter;
	
	uint8_t src_addr_mode, src_data_type, src_oper_mode;
	read_attrib(src_addr_mode, src_data_type, src_oper_mode);
	
	RAM_PTR src_addr;
	read_addr(src_addr, src_addr_mode);
	
	print_chr(ram_ptr_uint8(src_addr));
}

// Print a string into VRAM.
__inline void vm_inst_print_str()
{
    ++prg_counter;
	
	uint8_t src_addr_mode, src_data_type, src_oper_mode;
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
	
	print_str(&ram[src_addr]);
}

// Print a integer into VRAM.
__inline void vm_inst_print_int()
{
    ++prg_counter;
	
	uint8_t src_addr_mode, src_data_type, src_oper_mode;
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
	
	print_int(tmp.int32);
}

// Print a formatted text into VRAM.
__inline void vm_inst_printf_str()
{
    ++prg_counter;
}

// Copy a pixel sequence into specified VRAM coordinates.
__inline void vm_inst_draw_image()
{
    ++prg_counter;
    
}

// Load a script file from SD card to RAM to execute.
__inline void vm_inst_load_prg()
{
    ++prg_counter;
    
}

// Set the value of specified RAM area.
__inline void vm_inst_mem_set()
{
    ++prg_counter;
	
    uint8_t addr_mode, data_type, oper_mode;
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
	memset(&ram[dest_addr], val, length);
}

// Update the display with VRAM content.
__inline void vm_inst_update_display()
{
    ++prg_counter;
	//printf("update_display()\n\n");
	update_display();
}

// Notify game engine that we reached end of game logic loop, so it can do other stuff and start over.
__inline void vm_inst_end_of_loop()
{
	// TODO: Set program counter to start of the game logic loop.
	// Second thought: Maybe we can handle it by adding a jump instruction after this, so we won't have to store address of start of loop in RAM.
	end_of_loop_flag = 1;
}

// Save specified area of RAM to specified file.
__inline void vm_inst_save_to_file()
{
    ++prg_counter;
	
}

// Check if a key is currently pressed.
__inline void vm_inst_get_key()
{
    ++prg_counter;
	
}

// Check if a key is just pressed.
__inline void vm_inst_get_key_down()
{
    ++prg_counter;
	
}

// Check if a key is just released.
__inline void vm_inst_get_key_up()
{
    ++prg_counter;
	
}

// Check if a key is currently held.
__inline void vm_inst_get_key_held()
{
    ++prg_counter;
	
}

// Put a value in an array at specified index
__inline void vm_inst_array_assign()
{
	++prg_counter;
	
}

// Read the value from an array at specified index
__inline void vm_inst_array_get()
{
	++prg_counter;
	
}