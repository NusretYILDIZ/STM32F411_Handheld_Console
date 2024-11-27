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

#include "./keyboard.h"

#include "../assets/internal/keyboard_images.h"
#include "../graphics/graphics_2d.h"
#include "../../display/display_driver.h"
#include "../../input/input_driver.h"
#include "../../system/settings.h"
#include "../../system/timer.h"

#include <string.h>

// Actual keyboard position is one pixel upper but I cannot change the whole code.
#define KEYBOARD_HEIGHT  71
#define KEYBOARD_POS_Y   (DISPLAY_HEIGHT - KEYBOARD_HEIGHT - get_font_height() - 1)
//#define KEYBOARD_POS_Y   79
 
const uint8_t kb_layout_lowercase[4][10] = {
	{ '1', '2', '3', '4', '5', '6', '7', '8', '9', '0'  },
	{ 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p'  },
	{ 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', '\'' },
	{ 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '?'  },
};
 
const uint8_t kb_layout_uppercase[4][10] = {
	{ '1', '2', '3', '4', '5', '6', '7', '8', '9', '0'  },
	{ 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P'  },
	{ 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', '"'  },
	{ 'Z', 'X', 'C', 'V', 'B', 'N', 'M', ';', ':', '-'  },
};

const uint8_t kb_layout_symbols1[4][10] = {
	{ '1', '2', '3' , '4', '5', '6', '7', '8', '9', '0'  },
	{ '@', '#', '$' , '_', '&', '-', '+', '(', ')', '/'  },
	{ '*', '"', '\'', ':', ';', '!', '?', ',', '.', '\\' },
	{ '~', '|', '<' , '>', '{', '}', '[', ']', '^', '`'  },
};

const uint8_t kb_layout_symbols2[4][10] = {
	{ 127      , 127          , CHR_TR_C     , CHR_TR_O    , CHR_TR_I    , CHR_TR_S , CHR_TR_U , CHR_TR_G , 127        , 127         },
	{ 127      , 127          , CHR_TR_c     , CHR_TR_o    , CHR_TR_i    , CHR_TR_s , CHR_TR_u , CHR_TR_g , 127        , 127         },
	{ CHR_GP_UP, CHR_GP_RIGHT , CHR_GP_DOWN  , CHR_GP_LEFT , CHR_GP_X    , CHR_GP_Y , CHR_GP_A , CHR_GP_B , CHR_GP_HOME, CHR_GP_HOME },
	{ 127      , CHR_GP_SELECT, CHR_GP_SELECT, CHR_GP_START, CHR_GP_START, CHR_GP_L1, CHR_GP_L2, CHR_GP_R1, CHR_GP_R2  , 127         },
};

uint8_t text_buffer[MAX_INPUT_LEN + 1];

uint8_t selected_row = 2;
uint8_t selected_col = 4;
uint8_t kb_flags = 0;

uint8_t text_cursor_index;
int16_t text_cursor_x;
int16_t text_offset;
uint8_t text_len = 0;
uint8_t max_text_len;

void go_left_on_keyboard()
{
	if(!((kb_flags & KB_SYMBOLS) && (kb_flags & KB_SYMBOLS2)))
	{
		if(selected_col == 0) 
			selected_col = 9;
		
		else 
			selected_col--;
	}
	else
	{
		if(selected_row == 2)
		{
			if(selected_col >= 8 && selected_col <= 9)
				selected_col = 7;
			
			else if(selected_col == 0)
				selected_col = 9;
			
			else
				selected_col--;
		}
		else if(selected_row == 3)
		{
			if(selected_col >= 1 && selected_col <= 2)
				selected_col = 0;
			
			else if(selected_col >= 3 && selected_col <= 4)
				selected_col = 2;
			
			else if(selected_col == 0)
				selected_col = 9;
			
			else
				selected_col--;
		}
		else if(selected_col == 0)
			selected_col = 9;
		
		else
			selected_col--;
	}
}

void go_right_on_keyboard()
{
	if(!((kb_flags & KB_SYMBOLS) && (kb_flags & KB_SYMBOLS2)))
	{
		if(selected_col == 9)
			selected_col = 0;
		
		else
			selected_col++;
	}
	else  // Wide keys
	{
		if(selected_row == 2)
		{
			if(selected_col >= 8 && selected_col <= 9)
				selected_col = 0;
			
			else
				selected_col++;
		}
		else if(selected_row == 3)
		{
			if(selected_col >= 1 && selected_col <= 2)
				selected_col = 3;
			
			else if(selected_col >= 3 && selected_col <= 4)
				selected_col = 5;
			
			else if(selected_col == 9)
				selected_col = 0;
			
			else
				selected_col++;
		}
		else if(selected_col == 9)
			selected_col = 0;
		
		else selected_col++;
	}
}

void go_up_on_keyboard()
{
	if(selected_row == 0) selected_row = 3;
	else selected_row--;
}

void go_down_on_keyboard()
{
	if(selected_row == 3) selected_row = 0;
	else selected_row++;
}


void render_keyboard()
{
	fill_raw_rect(0, KEYBOARD_POS_Y - 1, 240, KEYBOARD_HEIGHT, 0);
	
	uint8_t colors[2] = {
		system_settings.theme_color_primary,
		system_settings.theme_color_secondary,
	};
	
	IMAGE key_img = {
		.palette = IMG_2_COLORS,
		.colors = (RAM_PTR)colors,
		.image = 0,
	};
	
	set_text_color(colors[1], colors[1]);
	
	// Render move cursor to left key
	fill_raw_rect(0, KEYBOARD_POS_Y, 19, 41, system_settings.theme_color_primary);
	set_cursor(7, KEYBOARD_POS_Y + 15);
	print_chr('<');
	set_cursor(4, KEYBOARD_POS_Y + 32);
	print_chr(CHR_GP_L1);
	
	// Render uppercase key
	fill_raw_rect(0, KEYBOARD_POS_Y + 42, 19, 27, system_settings.theme_color_primary);
	if(kb_flags & KB_SYMBOLS)
	{
		key_img.image = (kb_flags & KB_SYMBOLS2) ? (RAM_PTR)uppercase_enabled_icon : (RAM_PTR)uppercase_disabled_icon;
	}
	else
	{
		key_img.image = (kb_flags & KB_UPPERCASE) ? (RAM_PTR)uppercase_enabled_icon : (RAM_PTR)uppercase_disabled_icon;
	}
	draw_image_from_flash(5, KEYBOARD_POS_Y + 46, 9, 8, key_img);
	set_cursor(4, KEYBOARD_POS_Y + 67);
	print_chr(CHR_GP_L2);
	
	// Render symbols key
	fill_raw_rect(20, KEYBOARD_POS_Y + 56, 39, 13, system_settings.theme_color_primary);
	key_img.image = (kb_flags & KB_SYMBOLS) ? (RAM_PTR)letters_icon : (RAM_PTR)symbols_icon;
	draw_image_from_flash(23, KEYBOARD_POS_Y + 59, 17, 7, key_img);
	set_cursor(45, KEYBOARD_POS_Y + 68);
	print_chr(CHR_GP_R2);
	
	// Render space key
	fill_raw_rect(60, KEYBOARD_POS_Y + 56, 119, 13, system_settings.theme_color_primary);
	draw_formatted_text(119, KEYBOARD_POS_Y + 63, TEXT_H_ALIGN_CENTER | TEXT_V_ALIGN_CENTER, "%s %c", get_str(STR_SPACE), CHR_GP_X);
	
	// Render backspace key
	fill_raw_rect(180, KEYBOARD_POS_Y + 56, 39, 13, system_settings.theme_color_primary);
	key_img.image = (RAM_PTR)backspace_icon;
	draw_image_from_flash(184, KEYBOARD_POS_Y + 59, 13, 7, key_img);
	set_cursor(206, KEYBOARD_POS_Y + 68);
	print_chr(CHR_GP_B);
	
	// Render move cursor to right key
	fill_raw_rect(220, KEYBOARD_POS_Y, 19, 41, system_settings.theme_color_primary);
	set_cursor(227, KEYBOARD_POS_Y + 15);
	print_chr('>');
	set_cursor(224, KEYBOARD_POS_Y + 32);
	print_chr(CHR_GP_R1);
	
	// Render enter key
	fill_raw_rect(220, KEYBOARD_POS_Y + 42, 19, 27, system_settings.theme_color_primary);
	key_img.image = (RAM_PTR)enter_icon;
	draw_image_from_flash(225, KEYBOARD_POS_Y + 48, 8, 5, key_img);
	set_cursor(225, KEYBOARD_POS_Y + 67);
	print_chr(CHR_GP_Y);
	
	// Render letter keys
	for(int r = 0; r < 4; r++)
	{
		for(int c = 0; c < 10; c++)
		{
			if(selected_row == r && selected_col == c) 
			{
                colors[1] = system_settings.theme_color_primary;
                colors[0] = system_settings.theme_color_secondary;
            }
            else 
			{
                colors[1] = system_settings.theme_color_secondary;
                colors[0] = system_settings.theme_color_primary;
            }
			
            set_text_color(colors[1], colors[1]);
			
			int8_t chr;
			
			if(kb_flags & KB_SYMBOLS)
			{
				if(kb_flags & KB_SYMBOLS2) chr = kb_layout_symbols2[r][c];
				else chr = kb_layout_symbols1[r][c];
			}
			else
			{
				if(kb_flags & KB_UPPERCASE) chr = kb_layout_uppercase[r][c];
				else chr = kb_layout_lowercase[r][c];
			}
			
			if(!(kb_flags & KB_SYMBOLS && kb_flags & KB_SYMBOLS2))  // Other layouts
			{
				fill_raw_rect(20 + c*20, KEYBOARD_POS_Y + r*14, 19, 13, colors[0]);
				draw_char(29 + c*20, KEYBOARD_POS_Y + 7 + r*14, TEXT_H_ALIGN_CENTER | TEXT_V_ALIGN_CENTER, chr);
			}
			else  // Second layout of symbols, this needs special treatment because it has wide keys.
			{
				if(r == 2)  // Row 2 has 'HOME' key as wide key.
				{
					if(c == 8 || c == 9)  // 'HOME' key
					{
						fill_raw_rect(180, KEYBOARD_POS_Y + 28, 39, 13, colors[0]);
						draw_char(198, KEYBOARD_POS_Y + 35, TEXT_H_ALIGN_CENTER | TEXT_V_ALIGN_CENTER, chr);
						
						// TODO: Shorten this explanation because a normal human being will not read this.
						//
						// A wide key is equal to two normal keys in terms of width.
						// Keyboard render function iterates through all keys, so it processes the wide keys twice.
						// And since a wide key is made of two keys, we can select either part of the wide key to select it.
						//
						// Let's think that we selected the first part of a wide key.
						// When the first part gets processed, it gets rendered as selected, so everything is normal.
						// However, when the second part gets processed, it no longer is rendered as selected because we didn't select that second part.
						// This causes a wrong render, the key is being rendered not selected even it is actually selected.
						// To prevent this, if the first part is selected and if we processed the first part, skip the second part.
						if(c == 8 && selected_col == c) c++;
					}
					else  // Normal key
					{
						fill_raw_rect(20 + c*20, KEYBOARD_POS_Y + r*14, 19, 13, colors[0]);
						draw_char(29 + c*20, KEYBOARD_POS_Y + 7 + r*14, TEXT_H_ALIGN_CENTER | TEXT_V_ALIGN_CENTER, chr);
					}
				}
				else if(r == 3)  // Row 2 has 'SELECT' and 'START' keys as wide key.
				{
					if(c == 1 || c == 2)  // 'SELECT' key
					{
						fill_raw_rect(40, KEYBOARD_POS_Y + 42, 39, 13, colors[0]);
						draw_char(58, KEYBOARD_POS_Y + 49, TEXT_H_ALIGN_CENTER | TEXT_V_ALIGN_CENTER, chr);
						if(c == 1 && selected_col == c) c++;
					}
					else if(c == 3 || c == 4)  // 'START' key
					{
						fill_raw_rect(80, KEYBOARD_POS_Y + 42, 39, 13, colors[0]);
						draw_char(98, KEYBOARD_POS_Y + 49, TEXT_H_ALIGN_CENTER | TEXT_V_ALIGN_CENTER, chr);
						if(c == 3 && selected_col == c) c++;
					}
					else  // Normal key
					{
						fill_raw_rect(20 + c*20, KEYBOARD_POS_Y + r*14, 19, 13, colors[0]);
						draw_char(29 + c*20, KEYBOARD_POS_Y + 7 + r*14, TEXT_H_ALIGN_CENTER | TEXT_V_ALIGN_CENTER, chr);
					}
				}
				else  // Normal key
				{
					fill_raw_rect(20 + c*20, KEYBOARD_POS_Y + r*14, 19, 13, colors[0]);
					draw_char(29 + c*20, KEYBOARD_POS_Y + 7 + r*14, TEXT_H_ALIGN_CENTER | TEXT_V_ALIGN_CENTER, chr);
				}
			}
		}
	}
}

#define TEXT_BOX_WIDTH   222

void render_input_box(uint8_t *title, uint8_t cursor_on)
{
	fill_raw_rect(0, DISPLAY_HEIGHT - get_font_height() - 2, 240, get_font_height() + 2, system_settings.theme_color_primary);
	set_text_color(system_settings.theme_color_secondary, system_settings.theme_color_secondary);
	draw_formatted_text(4, DISPLAY_HEIGHT - 1, TEXT_H_ALIGN_LEFT | TEXT_V_ALIGN_BOTTOM, STR_GP_A"%s "STR_GP_START"%s", get_str(STR_ENTER_LETTER), get_str(STR_CANCEL));
	
	fill_raw_rect(0, 0, 240, KEYBOARD_POS_Y - 1, system_settings.theme_color_primary);
	set_text_color(system_settings.theme_color_secondary, system_settings.theme_color_secondary);
	draw_text(120, 5, TEXT_H_ALIGN_CENTER | TEXT_V_ALIGN_TOP, title);
	
	draw_raw_rect(6, 35, TEXT_BOX_WIDTH + 5, get_font_height() + 4, system_settings.theme_color_secondary);
	set_text_area(9, 37, TEXT_BOX_WIDTH + 8, 37 + get_font_height());
	set_text_wrap(0);
	
	uint16_t tw, th;
	int16_t tx, ty;
	text_bounds(text_buffer, 0, 0, &tx, &ty, &tw, &th);
	
	draw_text(9 - text_offset, 37, TEXT_H_ALIGN_LEFT | TEXT_V_ALIGN_TOP, text_buffer);
	
	// Draw cursor
	if(cursor_on)
	{
		draw_raw_v_line(8 + text_cursor_x, 37, get_font_height(), system_settings.theme_color_secondary);
	}
	
	set_text_area(0, 0, 239, 159);
}

void move_cursor_to_left()
{
	if(text_cursor_index > 0)
	{
		text_cursor_index--;
		uint8_t cw = get_char_width(text_buffer[text_cursor_index]);
		
		text_cursor_x -= cw;
		
		if(text_cursor_x < 0)
		{
			if(text_cursor_x + cw > 0) text_offset += text_cursor_x;
			else text_offset -= cw;
			
			text_cursor_x = 0;
			
			if(text_offset < 0) text_offset = 0;
		}
	}
}

void move_cursor_to_right()
{
	if(text_cursor_index < text_len)
	{
		uint8_t cw = get_char_width(text_buffer[text_cursor_index]);
		
		text_cursor_index++;
		text_cursor_x += cw;
		
		if(text_cursor_x > TEXT_BOX_WIDTH) 
		{
			if(text_cursor_x - cw < TEXT_BOX_WIDTH) text_offset += text_cursor_x - TEXT_BOX_WIDTH;
			else text_offset += cw;
			
			text_cursor_x = TEXT_BOX_WIDTH;
		}
	}
}

void move_cursor_after_delete()
{
	if(text_cursor_index > 0)
	{
		text_cursor_index--;
		uint8_t cw = get_char_width(text_buffer[text_cursor_index]);
		
		if(text_offset > 0)
		{
			if(text_offset >= cw) text_offset -= cw;
			else
			{
				text_cursor_x -= cw - text_offset;
				text_offset = 0;
			}
		}
		else text_cursor_x -= cw;
		
		if(text_cursor_x < 0) text_cursor_x = 0;
	}
}

void enter_letter(uint8_t letter)
{
	if(text_len < max_text_len && letter != 127)
	{
		// Push letters, which come after the cursor, to the right to make a space for the new letter.
		if(text_cursor_index < text_len)
		{
			// A fast alternative for memmove()
			// memcpy() doesn't work here, because destination and source are overlapping.
			// Also we need to work in reverse, we can't go from start to end (which memcpy() does).
			
			uint8_t *ptr = text_buffer + text_cursor_index;
			
			// Go to end of string, except the null terminator.
			while(*(ptr - 1) != '\0') ptr++;
			
			while(ptr > &text_buffer[text_cursor_index])
			{
				*ptr = *(ptr - 1);
				ptr--;
			}
		}
		
		text_buffer[text_cursor_index] = letter;
		text_len++;
		move_cursor_to_right();
	}
}

void press_key()
{
	if(kb_flags & KB_SYMBOLS)
	{
		if(kb_flags & KB_SYMBOLS2) enter_letter(kb_layout_symbols2[selected_row][selected_col]);
		else enter_letter(kb_layout_symbols1[selected_row][selected_col]);
	}
	else
	{
		if(kb_flags & KB_UPPERCASE) enter_letter(kb_layout_uppercase[selected_row][selected_col]);
		else enter_letter(kb_layout_lowercase[selected_row][selected_col]);
	}
}

void delete_letter()
{
	if(text_cursor_index > 0)
	{
		move_cursor_after_delete();
		memmove(&text_buffer[text_cursor_index], &text_buffer[text_cursor_index + 1], strlen(&text_buffer[text_cursor_index]));
		text_len--;
		text_buffer[text_len] = '\0';
	}
}

#define TEXT_CURSOR_BLINK_INTERVAL  15

void show_input_screen(RAM_PTR dest, uint8_t max_len, uint8_t *title, uint8_t modify)
{
	memset(text_buffer, '\0', sizeof(text_buffer));
	
	kb_flags = 0;
	max_text_len = max_len;
	
	text_cursor_index = 0;
	text_cursor_x = 0;
	text_offset = 0;
	
	uint8_t blink_timer = 0;
	uint8_t cursor_on = 1;
	
	if(modify)  // Copy the existing text at the destination to our buffer, so we can modify it.
	{
		RAM_PTR dest_ptr = dest;
		while(ram[dest_ptr] != '\0')
		{
			enter_letter(ram[dest_ptr]);
			dest_ptr++;
		}
	}
	
	for(;;)
	{
		render_input_box(title, cursor_on);
		render_keyboard();
		update_display();
		
		update_inputs();
		
		// Exit from keyboard
		if(get_key_down(GAMEPAD_START)) return;
		
		// Navigate on the keyboard
		if(get_key_down(GAMEPAD_DPAD_UP   ) || get_key_held_for_time(GAMEPAD_DPAD_UP   )) go_up_on_keyboard();
		if(get_key_down(GAMEPAD_DPAD_RIGHT) || get_key_held_for_time(GAMEPAD_DPAD_RIGHT)) go_right_on_keyboard();
		if(get_key_down(GAMEPAD_DPAD_DOWN ) || get_key_held_for_time(GAMEPAD_DPAD_DOWN )) go_down_on_keyboard();
		if(get_key_down(GAMEPAD_DPAD_LEFT ) || get_key_held_for_time(GAMEPAD_DPAD_LEFT )) go_left_on_keyboard();
		
		// Move cursor to left key
		if(get_key_down(GAMEPAD_L1) || get_key_held_for_time(GAMEPAD_L1))
		{
			cursor_on = 1;
			blink_timer = 0;
			move_cursor_to_left();
		}
		
		// Move cursor to right key
		if(get_key_down(GAMEPAD_R1) || get_key_held_for_time(GAMEPAD_R1))
		{
			cursor_on = 1;
			blink_timer = 0;
			move_cursor_to_right();
		}
		
		// Backspace key
		if(get_key_down(GAMEPAD_B ) || get_key_held_for_time(GAMEPAD_B ))
		{
			cursor_on = 1;
			blink_timer = 0;
			delete_letter();
		}
		
		// Space key
		if(get_key_down(GAMEPAD_X ) || get_key_held_for_time(GAMEPAD_X ))
		{
			cursor_on = 1;
			blink_timer = 0;
			enter_letter(' ');
		}
		
		// Uppercase key
		if(get_key_down(GAMEPAD_L2))
		{
			if(kb_flags & KB_SYMBOLS) kb_flags ^= KB_SYMBOLS2;
			else kb_flags ^= KB_UPPERCASE;
		}
		
		// Press the selected key
		if(get_key_down(GAMEPAD_A ) || get_key_held_for_time(GAMEPAD_A))
		{
			cursor_on = 1;
			blink_timer = 0;
			press_key();
		}

		// Symbols key
		if(get_key_down(GAMEPAD_R2))
		{
			kb_flags ^=  KB_SYMBOLS;
			kb_flags &= ~KB_SYMBOLS2;
		}

		// Enter key
		if(get_key_down(GAMEPAD_Y))
		{
			memcpy(&ram[dest], text_buffer, text_len + 1);  // Make sure we also copy the null terminator to prevent headaches.
			return;
		}
		
		wait_frame_time();
		blink_timer++;
		
		if(blink_timer >= TEXT_CURSOR_BLINK_INTERVAL)
		{
			cursor_on = !cursor_on;
			blink_timer = 0;
		}
	}
}