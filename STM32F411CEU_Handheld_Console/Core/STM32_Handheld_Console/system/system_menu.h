#ifndef __system_menu_h
#define __system_menu_h

#include "./locals/strings.h"

void change_lang(void);
void game_list(void);
/*{
	if(current_lang == strings_en) current_lang = strings_tr;
	else current_lang = strings_en;
}*/

const Menu_Item system_menu_items[] = {
	{ .text = STR_GAMES, .action = game_list },
	{ .text = STR_EDITOR },
	{ .text = STR_SETTINGS },
	{ .text = STR_ABOUT },
	{ .text = STR_LANGUAGE, .action = change_lang },
};

/*const Menu system_menu = {
	.x = 10,
	.y = 60,
	.w = 220,
	.visible_rows = 4,
	
	.non_selected_text_color = rgb888_to_rgb332(23, 139, 180),
	.non_selected_bg_color = rgb888_to_rgb332(23, 139, 180),
	.selected_text_color = rgb888_to_rgb332(105, 253, 255),
	.selected_bg_color = rgb888_to_rgb332(21, 72, 92),
	
	.attrib = CENTER_ALIGN,
	.font = 0,
	.capacity = 4,
	.selection = 0,
	.item_offset = 0,
	.items = system_menu_items,
};*/

#endif //__system_menu_h