#ifndef __internal_programs_h
#define __internal_programs_h

#include "../game_engine/game_engine.h"

const uint8_t test_code[] = {
	get_opcode(assign        ), ADDR_ABS | TYPE_INT8   , 255, 4 , 0, 0, ADDR_IMM | TYPE_INT8, 0,
	get_opcode(fill_display  ), ADDR_IMM | TYPE_UINT8  , rgb888_to_rgb332(50, 50, 150),
	get_opcode(set_cursor    ), ADDR_IMM | TYPE_INT16  , 10 , 0 , ADDR_IMM | TYPE_INT16, 20, 0,
	get_opcode(print_str     ), ADDR_IMM | TYPE_STRING , 'Z', 'i', 'k', 'i', 'r', 'm', 'a', 't', 'i', 'k', '\0',
	get_opcode(set_cursor    ), ADDR_IMM | TYPE_INT16  , 20 , 0 , ADDR_IMM | TYPE_INT16, 30, 0,
	get_opcode(set_text_color), ADDR_IMM | TYPE_UINT8  , 255, ADDR_IMM | TYPE_UINT8, 0,
	get_opcode(get_key_down  ), ADDR_IMM | TYPE_UINT16 , 1  , 0 ,
	get_opcode(jump_if_zero  ), ADDR_ABS | TYPE_RAM_PTR, 59 , 0 , 0, 0,
	get_opcode(increase      ), ADDR_ABS | TYPE_INT8   , 255, 4 , 0, 0,
	get_opcode(get_key_down  ), ADDR_IMM | TYPE_UINT16 , 4  , 0 ,
	get_opcode(jump_if_zero  ), ADDR_ABS | TYPE_RAM_PTR, 75 , 0 , 0, 0,
	get_opcode(decrease      ), ADDR_ABS | TYPE_INT8   , 255, 4 , 0, 0,
	get_opcode(print_int     ), ADDR_ABS | TYPE_INT8   , 255, 4 , 0, 0,
	get_opcode(get_key_down  ), ADDR_IMM | TYPE_UINT16 , 0  , 2 ,
	get_opcode(jump_if_zero  ), ADDR_ABS | TYPE_RAM_PTR, 92 , 0 , 0, 0,
	get_opcode(exit_game     ),
	get_opcode(end_of_loop   ),
	get_opcode(jump          ), ADDR_ABS | TYPE_RAM_PTR, 8  , 0 , 0, 0,
};

#endif //__internal_programs_h