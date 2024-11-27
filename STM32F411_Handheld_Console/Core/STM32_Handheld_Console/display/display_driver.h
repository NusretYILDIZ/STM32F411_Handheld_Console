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

#ifndef __display_driver_h
#define __display_driver_h

#include <stdint.h>
#include "./gfxfont.h"
#include "./fonts/fonts.h"
#include "../system/locals/special_chars.h"

#define DISPLAY_WIDTH   240
#define DISPLAY_HEIGHT  160

#define MAX_STRING_LEN  128

#define rgb888_to_rgb332(r, g, b)    ((((r) >> 5) << 5) | (((g) >> 5) << 2) | ((b) >> 6))

extern const uint16_t rgb332_to_rgb565[256];
extern uint8_t vram[DISPLAY_HEIGHT][DISPLAY_WIDTH];
extern int8_t str_buffer[MAX_STRING_LEN];

extern GFXfont *gfx_font;

extern int16_t cursor_x;
extern int16_t cursor_y;

extern uint8_t text_size_x;
extern uint8_t text_size_y;

typedef struct
{
	uint8_t start_x;
	uint8_t start_y;
	uint8_t end_x;
	uint8_t end_y;
} TextArea;

extern TextArea text_area;
extern uint8_t wrap_text;

extern uint8_t text_bg_color;
extern uint8_t text_fg_color;

uint8_t init_display(void);
void update_display(void);

void draw_raw_pixel(int16_t _x, int16_t _y, uint8_t color);
void draw_raw_v_line(int16_t x, int16_t y, int16_t h, uint8_t color);
void draw_raw_h_line(int16_t x, int16_t y, int16_t w, uint8_t color);
void draw_raw_rect(int16_t x, int16_t y, int16_t w, int16_t h, uint8_t color);
void fill_raw_rect(int16_t x, int16_t y, int16_t w, int16_t h, uint8_t color);
void draw_pixel(int16_t _x, int16_t _y, uint8_t color);
void draw_v_line(int16_t x, int16_t y, int16_t h, uint8_t color);
void draw_h_line(int16_t x, int16_t y, int16_t w, uint8_t color);
void draw_rect(int16_t x, int16_t y, int16_t w, int16_t h, uint8_t color);
void fill_rect(int16_t x, int16_t y, int16_t w, int16_t h, uint8_t color);
void fill_display(uint8_t color);
void clear_display(void);
void draw_bitmap(int16_t x, int16_t y, uint16_t w, uint16_t h, const uint8_t *image);

void set_cursor(int16_t x, int16_t y);
void set_text_size(uint8_t x, uint8_t y);
void set_text_color(uint8_t fg, uint8_t bg);
void set_text_wrap(uint8_t wrap);
void set_text_area(int16_t sx, int16_t sy, int16_t ex, int16_t ey);
void set_font_helper(const GFXfont *font);
void set_font(const uint8_t font);
GFXfont *get_current_font(void);
uint8_t get_font_height(void);
uint8_t get_char_width(unsigned char c);
void char_bounds(unsigned char c, int16_t *x, int16_t *y, int16_t *min_x, int16_t *min_y, int16_t *max_x, int16_t *max_y);
void text_bounds(const char *str, int16_t x, int16_t y, int16_t *x1, int16_t *y1, uint16_t *w, uint16_t *h);
void display_char(int16_t x, int16_t y, uint8_t c, uint8_t text_color, uint8_t bg_color, uint8_t size_x, uint8_t size_y);
void print_chr(uint8_t c);
void print_str(const char* str);
void print_int(long num);
void printf_str(const char *text, ...);

#endif // __display_driver_h
