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

#ifndef __graphics_2d_h
#define __graphics_2d_h

#include <stdarg.h>

#include "../script/script_engine.h"

typedef enum
{
	IMG_NO_PALETTE,
	IMG_2_COLORS,
	IMG_4_COLORS,
	IMG_16_COLORS,
} IMG_PALETTE;

typedef struct
{
	uint8_t palette;
	RAM_PTR colors;
	RAM_PTR image;
} IMAGE;

#define TEXT_H_ALIGN_LEFT    (0 << 0)
#define TEXT_H_ALIGN_CENTER  (1 << 0)
#define TEXT_H_ALIGN_RIGHT   (2 << 0)

#define TEXT_V_ALIGN_TOP     (0 << 2)
#define TEXT_V_ALIGN_CENTER  (1 << 2)
#define TEXT_V_ALIGN_BOTTOM  (2 << 2)

#define TEXT_H_ALIGN_MASK  (3 << 0)
#define TEXT_V_ALIGN_MASK  (3 << 2)

#define get_text_h_align(x)  (x & TEXT_H_ALIGN_MASK)
#define get_text_v_align(x)  (x & TEXT_V_ALIGN_MASK)

void draw_image(int16_t x, int16_t y, uint16_t w, uint16_t h, IMAGE image);
void draw_image_from_flash(int16_t x, int16_t y, uint16_t w, uint16_t h, IMAGE image);
void draw_text(int16_t x, int16_t y, uint8_t text_flags, char *text);
void draw_formatted_text(int16_t x, int16_t y, uint8_t text_flags, char *text, ...);
void draw_char(int16_t x, int16_t y, uint8_t text_flags, char c);

#endif //__graphics_2d_h