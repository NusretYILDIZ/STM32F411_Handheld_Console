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
	get_opcode(set_cursor    ), ADDR_IMM | TYPE_INT16  , 10 , 0 , ADDR_IMM | TYPE_INT16, 40, 0,
	get_opcode(print_str     ), ADDR_IMM | TYPE_STRING , '(', '3', '+', 'x', ')', '*', '(', '4', '-', 'x', ')', '=', '\0',
	get_opcode(evaluate_rpn  ), ADDR_ABS | TYPE_INT32   , 255, 5 , 0, 0,                     // destination
	                            RPN_TYPE_NUMERAL, ADDR_IMM | TYPE_INT8, 0, 0, 3, 0, 0, 0,    // 3
								RPN_TYPE_NUMERAL, ADDR_ABS | TYPE_INT8, 0, 0, 255, 4, 0, 0,  // x
								RPN_TYPE_ADD, 0, 0, 0, 0, 0, 0, 0,                           // +
								RPN_TYPE_NUMERAL, ADDR_IMM | TYPE_INT8, 0, 0, 4, 0, 0, 0,    // 4
								RPN_TYPE_NUMERAL, ADDR_ABS | TYPE_INT8, 0, 0, 255, 4, 0, 0,  // x
								RPN_TYPE_SUB, 0, 0, 0, 0, 0, 0, 0,                           // -
								RPN_TYPE_MUL, 0, 0, 0, 0, 0, 0, 0,                           // *
	                            RPN_TYPE_TERMINATE, 0, 0, 0, 0, 0, 0, 0, 
	get_opcode(print_int     ), ADDR_ABS | TYPE_INT32   , 255, 5 , 0, 0, 
	get_opcode(set_cursor    ), ADDR_IMM | TYPE_INT16   , 10 , 0 , ADDR_IMM | TYPE_INT16, 150, 0,
	get_opcode(print_str     ), ADDR_IMM | TYPE_STRING  , CHR_GP_X, 'C', 'r', 'a', 's', 'h', ' ', CHR_GP_UP, 'A', 'r', 't', 't', CHR_TR_i, 'r', ' ', CHR_GP_DOWN, 'A', 'z', 'a', 'l', 't', ' ', CHR_GP_HOME, CHR_TR_C, CHR_TR_i, 'k', CHR_TR_i, CHR_TR_s, '\0',
	get_opcode(get_key_down  ), ADDR_IMM | TYPE_UINT16  , 16 , 0,
	get_opcode(jump_if_zero  ), ADDR_ABS | TYPE_RAM_PTR , 239 , 0 , 0, 0,
	get_opcode(invalid       ),
	get_opcode(end_of_loop   ),
	get_opcode(jump          ), ADDR_ABS | TYPE_RAM_PTR, 8  , 0 , 0, 0,
};

#endif //__internal_programs_h