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

#include "../display/display_driver.h"
#include "./menu.h"
#include "./popup.h"

#ifndef NULL
#define NULL  0
#endif

void menu_render(MENU *menu)
{
	GFXfont *temp = get_current_font();
	set_font_helper(menu->data->font);
	
	if(menu->data->non_selected_text_color != menu->data->non_selected_bg_color) 
		fill_raw_rect(menu->data->x, menu->data->y, menu->data->w, menu->data->visible_rows * get_font_height(), menu->data->non_selected_bg_color);
	
	if(menu->data->selected_text_color != menu->data->selected_bg_color)
		fill_raw_rect(menu->data->x, menu->data->y + get_font_height() * (menu->selection - menu->item_offset), menu->data->w, get_font_height(), menu->data->selected_bg_color);
	
	set_text_area(menu->data->x + 3, menu->data->y, menu->data->x + menu->data->w - 3, menu->data->y + menu->data->visible_rows * get_font_height());
	
	for(uint8_t i = 0; i < menu->data->visible_rows; ++i)
	{
		MENU_ITEM *current_item = menu_get_item(menu, i + menu->item_offset);
		//printf("%d. item = %s\n", i, get_str(current_item->text));
		
		if((menu->data->attrib & RIGHT_ALIGN) || (menu->data->attrib & CENTER_ALIGN))
		{
			int16_t tx, ty;
			uint16_t tw, th;
			//text_bounds(menu->data->items[menu->item_offset + i].text, 0, 0, &tx, &ty, &tw, &th);
			//text_bounds(current_item->text, 0, 0, &tx, &ty, &tw, &th);
			if(menu->data->attrib & SYSTEM_MENU)
				text_bounds(get_str(current_item->menu_text.string), 0, 0, &tx, &ty, &tw, &th);
			else
				text_bounds(current_item->menu_text.text, 0, 0, &tx, &ty, &tw, &th);
			
			set_cursor((menu->data->attrib & RIGHT_ALIGN) ? (menu->data->x + menu->data->w - tw - 3) : (menu->data->x + (menu->data->w - tw) / 2 - 3), 
						menu->data->y + get_font_height() * (i + 1));
		}
		else
		{
			set_cursor(menu->data->x + 3, menu->data->y + get_font_height() * (i + 1));
		}
		
		uint8_t temp_color = (menu->selection - menu->item_offset == i) ? menu->data->selected_text_color : menu->data->non_selected_text_color;
		set_text_color(temp_color, temp_color);
		//print_str(menu->data->items[menu->item_offset + i].text);
		//print_str(current_item->text);
		if(menu->data->attrib & SYSTEM_MENU)
			print_str(get_str(current_item->menu_text.string));
		else
			print_str(current_item->menu_text.text);
	}
	
	set_font_helper(temp);
}

void menu_prev_item(MENU *menu)
{
	if(menu->selection > 0) 
	{
		menu->selection--;
		
		if(menu->selection < menu->item_offset)
			menu->item_offset--;
	}
}

void menu_next_item(MENU *menu)
{
	if(menu->selection < menu->data->capacity - 1)
	{
		menu->selection++;
		
		if(menu->selection >= menu->item_offset + menu->data->visible_rows)
			menu->item_offset++;
	}
}

void menu_select(MENU *menu)
{
	//if(menu->items[menu->selection].action) menu->items[menu->selection].action();
	MENU_ITEM *current_item = menu_get_current_item(menu);
	if(current_item->action) current_item->action();
}

MENU_ITEM *menu_get_current_item(MENU *menu)
{
	//return &((MENU_ITEM *)(&ram[menu->items]))[menu->selection];
	return &menu->data->items[menu->selection];
}

MENU_ITEM *menu_get_item(MENU *menu, MENU_INDEX index)
{
	//return &((MENU_ITEM *)(&ram[menu->items]))[index];
	return &menu->data->items[index];
}