#ifndef __system_menu_h
#define __system_menu_h

#include "./locals/strings.h"
#include "../display/YILDIZsoft_5x7.h"

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
	.font = &YILDIZsoft_5x7,
	.capacity = 5,
	//.selection = 0,
	//.item_offset = 0,
	.items = system_menu_items,
};

#endif //__system_menu_h