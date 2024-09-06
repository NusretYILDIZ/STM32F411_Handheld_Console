#include "./keyboard.h"

#include "../assets/internal/keyboard_images.h"
#include "../graphics/graphics_2d.h"
#include "../../display/display_driver.h"
#include "../../input/input_driver.h"
#include "../../system/settings.h"
#include "../../system/timer.h"

/**
 *    Keyboard Layout
 *
 *       Col 0 1 2 3 4 5 6 7 8 9 10 11
 *
 *    Row 0  < 1 2 3 4 5 6 7 8 9 0 >
 *    Row 1  < Q W E R T Y U I O P >
 *    Row 2  < A S D F G H J K L ' >
 *    Row 3  ^ Z X C V B N M , . - enter
 *    Row 4  ^ #!& ! [Space] ? bck enter
 */

typedef enum
{
	KEY_TYPE_LETTER,
	KEY_TYPE_CURSOR_LEFT,
	KEY_TYPE_CURSOR_RIGHT,
	KEY_TYPE_UPPERCASE,
	KEY_TYPE_SYMBOLS,
	KEY_TYPE_SPACE,
	KEY_TYPE_BACKSPACE,
	KEY_TYPE_ENTER,
} KB_KEY_TYPE;

const uint8_t kb_layout[5][12] = {
	{ KEY_TYPE_CURSOR_LEFT, KEY_TYPE_LETTER , KEY_TYPE_LETTER , KEY_TYPE_LETTER, KEY_TYPE_LETTER, KEY_TYPE_LETTER, KEY_TYPE_LETTER, KEY_TYPE_LETTER, KEY_TYPE_LETTER, KEY_TYPE_LETTER   , KEY_TYPE_LETTER   , KEY_TYPE_CURSOR_RIGHT },
	{ KEY_TYPE_CURSOR_LEFT, KEY_TYPE_LETTER , KEY_TYPE_LETTER , KEY_TYPE_LETTER, KEY_TYPE_LETTER, KEY_TYPE_LETTER, KEY_TYPE_LETTER, KEY_TYPE_LETTER, KEY_TYPE_LETTER, KEY_TYPE_LETTER   , KEY_TYPE_LETTER   , KEY_TYPE_CURSOR_RIGHT },
	{ KEY_TYPE_CURSOR_LEFT, KEY_TYPE_LETTER , KEY_TYPE_LETTER , KEY_TYPE_LETTER, KEY_TYPE_LETTER, KEY_TYPE_LETTER, KEY_TYPE_LETTER, KEY_TYPE_LETTER, KEY_TYPE_LETTER, KEY_TYPE_LETTER   , KEY_TYPE_LETTER   , KEY_TYPE_CURSOR_RIGHT },
	{ KEY_TYPE_UPPERCASE  , KEY_TYPE_LETTER , KEY_TYPE_LETTER , KEY_TYPE_LETTER, KEY_TYPE_LETTER, KEY_TYPE_LETTER, KEY_TYPE_LETTER, KEY_TYPE_LETTER, KEY_TYPE_LETTER, KEY_TYPE_LETTER   , KEY_TYPE_LETTER   , KEY_TYPE_ENTER        },
	{ KEY_TYPE_UPPERCASE  , KEY_TYPE_SYMBOLS, KEY_TYPE_SYMBOLS, KEY_TYPE_SPACE , KEY_TYPE_SPACE , KEY_TYPE_SPACE , KEY_TYPE_SPACE , KEY_TYPE_SPACE , KEY_TYPE_SPACE , KEY_TYPE_BACKSPACE, KEY_TYPE_BACKSPACE, KEY_TYPE_ENTER        },
};
 
const int8_t kb_layout_lowercase[4][10] = {
	{ '1', '2', '3', '4', '5', '6', '7', '8', '9', '0'  },
	{ 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p'  },
	{ 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', '\'' },
	{ 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '-'  },
};
 
const int8_t kb_layout_uppercase[4][10] = {
	{ '1', '2', '3', '4', '5', '6', '7', '8', '9', '0'  },
	{ 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P'  },
	{ 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', '"'  },
	{ 'Z', 'X', 'C', 'V', 'B', 'N', 'M', ';', ':', '_'  },
};

uint8_t selected_row = 2;
uint8_t selected_col = 5;
uint8_t kb_flags = 0;

void go_left_on_keyboard()
{
	if(selected_col == 0) return;
	
	if(selected_row != 4) selected_col--;
	else
	{
		if(selected_col == 1 || selected_col == 2)  // Symbols key
			selected_col = 0;
		else if(selected_col >= 3 && selected_col <= 8)  // Space key
			selected_col = 2;
		else if(selected_col == 9 || selected_col == 10)  // Backspace key
			selected_col = 8;
		else
			selected_col--;
	}
}

void go_right_on_keyboard()
{
	if(selected_col == 11) return;
	
	if(selected_row != 4) selected_col++;
	else
	{
		if(selected_col == 1 || selected_col == 2)  // Symbols key
			selected_col = 3;
		else if(selected_col >= 3 && selected_col <= 8)  // Space key
			selected_col = 9;
		else if(selected_col == 9 || selected_col == 10)  // Backspace key
			selected_col = 11;
		else
			selected_col++;
	}
}

void go_up_on_keyboard()
{
	if(selected_row == 0) return;
	
	if(selected_col != 0 && selected_col != 11) 
		selected_row--;
	else if(selected_row == 3 || selected_row == 4)  // Uppercase & enter keys
		selected_row = 2;
}

void go_down_on_keyboard()
{
	if(selected_row == 4) return;
	
	if(selected_col != 0 && selected_col != 11) 
		selected_row++;
	else if(selected_row >= 0 || selected_row <= 2)  // Move cursor to left & Move cursor to right keys
		selected_row = 3;
}

void render_input_box(char *title)
{
	set_text_color(system_settings.theme_color_secondary, system_settings.theme_color_secondary);
	draw_text(120, 5, TEXT_H_ALIGN_CENTER | TEXT_V_ALIGN_CENTER, title);
}


#define set_key_color(cond)  do { \
                                 if(cond) { \
                                     colors[1] = system_settings.theme_color_primary; \
                                     colors[0] = system_settings.theme_color_secondary; \
                                 } \
                                 else { \
                                     colors[1] = system_settings.theme_color_secondary; \
                                     colors[0] = system_settings.theme_color_primary; \
                                 } \
                                 set_text_color(colors[1], colors[1]); \
                             } while(0)

void render_keyboard()
{
	set_cursor(2, 159);
	set_text_color(system_settings.theme_color_secondary, system_settings.theme_color_secondary);
	printf_str(STR_GP_A"%s "STR_GP_START"%s", get_str(STR_ENTER_LETTER), get_str(STR_DONE));
	
	uint8_t colors[2] = {
		system_settings.theme_color_primary,
		system_settings.theme_color_secondary,
	};
	
	IMAGE key_img = {
		.palette = IMG_2_COLORS,
		.colors = (RAM_PTR)colors,
		.image = 0,
	};
	
	// Render move cursor to left key
	set_key_color(selected_col == 0 && (selected_row >= 0 && selected_row <= 2));
	key_img.image = (RAM_PTR)upper_side_keys;
	draw_image_from_flash(0, 78, 19, 41, key_img);
	set_cursor(7, 94);
	print_chr('<');
	set_cursor(4, 111);
	print_chr(CHR_GP_L1);
	
	// Render uppercase key
	set_key_color(selected_col == 0 && (selected_row >= 3 && selected_row <= 4));
	key_img.image = (RAM_PTR)uppercase_key;
	draw_image_from_flash(0, 120, 19, 27, key_img);
	set_cursor(4, 145);
	print_chr(CHR_GP_L2);
	
	// Render symbols key
	set_key_color(selected_row == 4 && selected_col >= 1 && selected_col <= 2);
	key_img.image = (RAM_PTR)symbols_key;
	draw_image_from_flash(20, 134, 39, 13, key_img);
	set_cursor(44, 146);
	print_chr(CHR_GP_R2);
	
	// Render space key
	set_key_color(selected_row == 4 && selected_col >= 3 && selected_col <= 8);
	key_img.image = (RAM_PTR)space_key;
	draw_image_from_flash(60, 134, 119, 13, key_img);
	draw_formatted_text(119, 135, TEXT_H_ALIGN_CENTER | TEXT_V_ALIGN_CENTER, "%s %c", get_str(STR_SPACE), CHR_GP_X);
	
	// Render backspace key
	set_key_color(selected_row == 4 && selected_col >= 9 && selected_col <= 10);
	key_img.image = (RAM_PTR)backspace_key;
	draw_image_from_flash(180, 134, 39, 13, key_img);
	set_cursor(206, 146);
	print_chr(CHR_GP_B);
	
	// Render move cursor to right key
	set_key_color(selected_col == 11 && (selected_row >= 0 && selected_row <= 2));
	key_img.image = (RAM_PTR)upper_side_keys;
	draw_image_from_flash(220, 78, 19, 41, key_img);
	set_cursor(227, 94);
	print_chr('>');
	set_cursor(224, 111);
	print_chr(CHR_GP_R1);
	
	// Render enter key
	set_key_color(selected_col == 11 && (selected_row >= 3 && selected_row <= 4));
	key_img.image = (RAM_PTR)enter_key;
	draw_image_from_flash(220, 120, 19, 27, key_img);
	set_cursor(225, 145);
	print_chr(CHR_GP_Y);
	
	// Render letter keys
	key_img.image = (RAM_PTR)letter_keys;
	for(int r = 0; r < 4; r++)
	{
		for(int c = 0; c < 10; c++)
		{
			set_key_color(selected_row == r && selected_col == (c + 1));
			draw_image_from_flash(20 + c*20, 78 + r*14, 19, 13, key_img);
			
			draw_char(29 + c*20, 79 + r*14, TEXT_H_ALIGN_CENTER | TEXT_V_ALIGN_CENTER, (kb_flags & KB_UPPERCASE) ? kb_layout_uppercase[r][c] : kb_layout_lowercase[r][c]);
		}
	}
}

#undef set_key_color

void show_input_screen(RAM_PTR dest, INPUT_LEN max_len, char *title)
{
	for(;;)
	{
		render_input_box(title);
		render_keyboard();
		update_display();
		
		update_inputs();
		
		if(get_key_down(GAMEPAD_START)) return;
		
		if(get_key_down(GAMEPAD_DPAD_UP   ) || get_key_held_for_time(GAMEPAD_DPAD_UP   )) go_up_on_keyboard();
		if(get_key_down(GAMEPAD_DPAD_RIGHT) || get_key_held_for_time(GAMEPAD_DPAD_RIGHT)) go_right_on_keyboard();
		if(get_key_down(GAMEPAD_DPAD_DOWN ) || get_key_held_for_time(GAMEPAD_DPAD_DOWN )) go_down_on_keyboard();
		if(get_key_down(GAMEPAD_DPAD_LEFT ) || get_key_held_for_time(GAMEPAD_DPAD_LEFT )) go_left_on_keyboard();
		
		if(get_key_down(GAMEPAD_L2)) kb_flags ^= KB_UPPERCASE;
		
		wait_frame_time();
	}
}