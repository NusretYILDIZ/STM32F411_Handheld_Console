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

#ifndef __system_menu_h
#define __system_menu_h

#include "./locals/strings.h"
#include "../display/fonts/fonts.h"

void change_lang(void);
void game_list(void);
/*{
	if(current_lang == strings_en) current_lang = strings_tr;
	else current_lang = strings_en;
}*/

const MENU_ITEM system_menu_items[] = {
	{ .menu_text.string = STR_GAMES, .action = game_list },
	{ .menu_text.string = STR_EDITOR },
	{ .menu_text.string = STR_SETTINGS },
	{ .menu_text.string = STR_ABOUT },
	{ .menu_text.string = STR_LANGUAGE, .action = change_lang },
};

const MENU_DATA system_menu_data = {
	.x = 10,
	.y = 60,
	.w = 220,
	.visible_rows = 5,
	
	.non_selected_text_color = rgb888_to_rgb332(23, 139, 180),
	.non_selected_bg_color = rgb888_to_rgb332(23, 139, 180),
	.selected_text_color = rgb888_to_rgb332(105, 253, 255),
	.selected_bg_color = rgb888_to_rgb332(21, 72, 92),
	
	.attrib = CENTER_ALIGN | SYSTEM_MENU,
	.font = &Minecraft_5x7,
	.capacity = 5,
	//.selection = 0,
	//.item_offset = 0,
	.items = system_menu_items,
};

#endif //__system_menu_h