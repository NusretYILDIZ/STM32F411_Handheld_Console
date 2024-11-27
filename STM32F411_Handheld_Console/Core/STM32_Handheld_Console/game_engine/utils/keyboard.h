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

#ifndef __keyboard_h
#define __keyboard_h

#include "../script/script_engine.h"

#define KB_UPPERCASE  (1 << 0)
#define KB_SYMBOLS    (1 << 1)
#define KB_SYMBOLS2   (1 << 2)

#define MAX_INPUT_LEN  (127)

extern uint8_t text_buffer[MAX_INPUT_LEN + 1];

extern uint8_t selected_row;
extern uint8_t selected_col;
extern uint8_t kb_flags;

void show_input_screen(RAM_PTR dest, uint8_t max_len, uint8_t *title, uint8_t modify);

#endif //__keyboard_h