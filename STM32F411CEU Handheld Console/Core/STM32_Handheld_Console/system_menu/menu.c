#include "../display/display_driver.h"
#include "./menu.h"
#include "./popup.h"

#ifndef NULL
#define NULL  0
#endif

void menu_render(Menu *menu)
{
	assertion(menu->selection < menu->capacity, "Men"TR_u" se"TR_c"imi men"TR_u" kapasitesinden b"TR_u"y"TR_u"k.");

	fill_raw_rect(menu->x, menu->y, menu->w, menu->rows * get_font_height() * 2, menu->bg_color);
	fill_raw_rect(menu->x, menu->y + get_font_height() * (menu->selection - menu->item_shift) * 2, menu->w, get_font_height() * 2, menu->selection_bg_color);
	
	set_text_area(menu->x + 3, menu->y, menu->x + menu->w - 6, menu->y + menu->rows * get_font_height() * 2);
	set_cursor(menu->x + 3, menu->y + get_font_height() * 2);
	set_text_size(2, 2);
	
	for(uint8_t i = 0; i < menu->rows; ++i)
	{
		uint8_t temp_color = (menu->selection - menu->item_shift == i) ? menu->selected_text_color : menu->non_selected_text_color;
		set_text_color(temp_color, temp_color);
		print_str(menu->items[menu->item_shift + i].text);
		print_chr('\n');
	}
	
	set_text_size(1, 1);
}

void menu_go_up(Menu *menu)
{
	if(menu->selection > 0) 
	{
		menu->selection--;
		
		if(menu->selection < menu->item_shift)
			menu->item_shift--;
	}
}

void menu_go_down(Menu *menu)
{
	if(menu->selection < menu->capacity - 1)
	{
		menu->selection++;
		
		if(menu->selection >= menu->item_shift + menu->rows)
			menu->item_shift++;
	}
}

void menu_select(Menu *menu)
{
	assertion(menu->selection < menu->capacity, "Men"TR_u" se"TR_c"imi men"TR_u" kapasitesinden b"TR_u"y"TR_u"k.");
	assertion(menu->items[menu->selection].action != NULL, "Se"TR_c"enekte ge"TR_c"erli bir fonksiyon yok.");
	
	menu->items[menu->selection].action();
}