/*
	MIT License

	Copyright (c) 2024 Nusret YILDIZ

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/

#ifndef __instructions_h
#define __instructions_h

#define INST_TABLE(X)   X(invalid) \
                        X(assign) \
						X(increase) \
						X(decrease) \
                        X(evaluate_rpn) \
                        X(call_no_arg) \
                        X(call_with_arg) \
                        X(return_no_val) \
                        X(return_with_val) \
						X(jump_if_carry) \
						X(jump_if_zero) \
                        X(jump_if) \
                        X(jump) \
                        X(exit_game) \
                        X(set_text_area) \
                        X(set_cursor) \
                        X(set_text_color) \
                        X(set_text_size) \
                        X(set_text_wrap) \
                        X(clr_text_wrap) \
                        X(set_font) \
                        X(print_chr) \
                        X(print_str) \
                        X(print_int) \
                        X(printf_str) \
                        X(draw_bitmap) \
						X(fill_display) \
                        X(update_display) \
                        X(load_prg) \
                        X(mem_set) \
						X(end_of_loop) \
						X(syscall) \
						X(get_key) \
						X(get_key_down) \
						X(get_key_up) \
						X(get_key_held) \
						X(get_key_held_for_time) \
						X(sdcard_init) \
						X(sdcard_deinit) \
						X(file_exists) \
						X(dir_exists) \
						X(file_full_read) \
						X(file_read) \
						X(file_append) \
						X(file_write) \
						X(file_rename) \
						X(file_size) \
						X(create_dir) \
						X(delete_file) \
						X(delete_dir) \

#define ENUM_OPCODE(ins)  enum_inst_##ins,
typedef enum e_OPCODE
{
	INST_TABLE(ENUM_OPCODE)
} OPCODE;
#undef ENUM_OPCODE

#define get_opcode(ins)  enum_inst_##ins

#define INST_DECLARE(ins)  void vm_inst_##ins(void);
INST_TABLE(INST_DECLARE)
#undef INST_DECLARE

#endif //__instructions_h