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

#include <string.h>
#include <stdio.h>

#include "./popup.h"
#include "./timer.h"
#include "../display/display_driver.h"
#include "../input/input_driver.h"

#define ERROR_COLOR    rgb888_to_rgb332(200, 20, 20)
#define INFO_COLOR     rgb888_to_rgb332(50, 50, 200)

#define WINDOW_X         25
#define WINDOW_Y         25
#define WINDOW_WIDTH     (DISPLAY_WIDTH - 2 * WINDOW_X)
#define WINDOW_HEIGHT    (DISPLAY_HEIGHT - 2 * WINDOW_Y)

void show_window_helper(const char *title, const char *msg, unsigned char color)
{
	draw_raw_rect(WINDOW_X, WINDOW_Y, WINDOW_WIDTH, WINDOW_HEIGHT, color);
	fill_raw_rect(WINDOW_X + 1, WINDOW_Y + 1, WINDOW_WIDTH - 2, WINDOW_HEIGHT - 2, 0);
	
	int16_t text_x, text_y;
	uint16_t text_w, text_h;
	
	text_bounds(title, 0, 0, &text_x, &text_y, &text_w, &text_h);
	fill_raw_rect(WINDOW_X + 1, WINDOW_Y + 1, WINDOW_WIDTH - 1, get_font_height() + 2, color);
	
	set_text_area(WINDOW_X + 4, WINDOW_Y, WINDOW_X + WINDOW_WIDTH - 8, WINDOW_Y + WINDOW_HEIGHT - 4);
	set_cursor(WINDOW_X + (WINDOW_WIDTH - text_w) / 2, WINDOW_Y + get_font_height() + 1);
	uint8_t temp_fg = text_fg_color;
	uint8_t temp_bg = text_bg_color;
	set_text_color(0xff, 0xff);
	print_str(title);
	print_str("\n");
	
	uint8_t temp_wrap = wrap_text;
	set_text_wrap(1);
	//set_text_area(WINDOW_X + 4, cursor_y - text_h + 3, WINDOW_X + WINDOW_WIDTH - 8, WINDOW_Y + WINDOW_HEIGHT - 3);
	
	text_bounds(msg, 0, 0, &text_x, &text_y, &text_w, &text_h);
	set_cursor(WINDOW_X + 4, cursor_y + 3);
	print_str(msg);
	
	fill_raw_rect(WINDOW_X + 45, WINDOW_Y + WINDOW_HEIGHT - 2 * get_font_height(), 100, get_font_height() + 2, color);
	text_bounds(get_str(STR_OK), 0, 0, &text_x, &text_y, &text_w, &text_h);
	set_cursor(WINDOW_X + (WINDOW_WIDTH - text_w) / 2, WINDOW_Y + WINDOW_HEIGHT - get_font_height() + 1);
	print_str(get_str(STR_OK));
	
	update_display();
	
	for(;;)
	{
		update_inputs();
		if(get_key_down(GAMEPAD_A)) break;
		system_sleep(33);
	}
	
	set_text_wrap(temp_wrap);
	set_text_color(temp_fg, temp_bg);
}

void show_error_window(const char *title, const char *msg)
{
	show_window_helper(title, msg, ERROR_COLOR);
}

void show_info_window(const char *title, const char *msg)
{
	show_window_helper(title, msg, INFO_COLOR);
}

void _test_assertion(const char *e, const char *file_name, int line)
{
	char msg[180] = { '\0' };
	snprintf(msg, sizeof(msg), "%s\n\nFile: %s\nLine: %d", e, file_name, line);
	
	show_error_window("ASSERTION FAILED", msg);
	
	update_display();
	while(1);
}