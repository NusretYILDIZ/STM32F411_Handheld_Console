#include "../display/display_driver.h"
#include "./menu.h"
#include "./popup.h"

#ifndef NULL
#define NULL  0
#endif

void menu_render(Menu *menu)
{
	GFXfont *temp = get_current_font();
	set_font_helper(menu->font);
	
	if(menu->non_selected_text_color != menu->non_selected_bg_color) 
		fill_raw_rect(menu->x, menu->y, menu->w, menu->visible_rows * get_font_height(), menu->non_selected_bg_color);
	
	if(menu->selected_text_color != menu->selected_bg_color)
		fill_raw_rect(menu->x, menu->y + get_font_height() * (menu->selection - menu->item_offset), menu->w, get_font_height(), menu->selected_bg_color);
	
	set_text_area(menu->x + 3, menu->y, menu->x + menu->w - 3, menu->y + menu->visible_rows * get_font_height());
	
	for(uint8_t i = 0; i < menu->visible_rows; ++i)
	{
		Menu_Item *current_item = menu_get_item(menu, i + menu->item_offset);
		//printf("%d. item = %s\n", i, get_str(current_item->text));
		
		if((menu->attrib & RIGHT_ALIGN) || (menu->attrib & CENTER_ALIGN))
		{
			int16_t tx, ty;
			uint16_t tw, th;
			//text_bounds(menu->items[menu->item_offset + i].text, 0, 0, &tx, &ty, &tw, &th);
			//text_bounds(current_item->text, 0, 0, &tx, &ty, &tw, &th);
			text_bounds(current_item->text, 0, 0, &tx, &ty, &tw, &th);
			set_cursor((menu->attrib & RIGHT_ALIGN) ? (menu->x + menu->w - tw - 3) : (menu->x + (menu->w - tw) / 2 - 3), 
						menu->y + get_font_height() * (i + 1));
		}
		else
		{
			set_cursor(menu->x + 3, menu->y + get_font_height() * (i + 1));
		}
		
		uint8_t temp_color = (menu->selection - menu->item_offset == i) ? menu->selected_text_color : menu->non_selected_text_color;
		set_text_color(temp_color, temp_color);
		//print_str(menu->items[menu->item_offset + i].text);
		//print_str(current_item->text);
		print_str(current_item->text);
	}
	
	set_font_helper(temp);
}

void menu_prev_item(Menu *menu)
{
	if(menu->selection > 0) 
	{
		menu->selection--;
		
		if(menu->selection < menu->item_offset)
			menu->item_offset--;
	}
}

void menu_next_item(Menu *menu)
{
	if(menu->selection < menu->capacity - 1)
	{
		menu->selection++;
		
		if(menu->selection >= menu->item_offset + menu->visible_rows)
			menu->item_offset++;
	}
}

void menu_select(Menu *menu)
{
	//if(menu->items[menu->selection].action) menu->items[menu->selection].action();
	Menu_Item *current_item = menu_get_current_item(menu);
	if(current_item->action) current_item->action();
}

Menu_Item *menu_get_current_item(Menu *menu)
{
	//return &((Menu_Item *)(&ram[menu->items]))[menu->selection];
	return &menu->items[menu->selection];
}

Menu_Item *menu_get_item(Menu *menu, MENU_INDEX index)
{
	//return &((Menu_Item *)(&ram[menu->items]))[index];
	return &menu->items[index];
}