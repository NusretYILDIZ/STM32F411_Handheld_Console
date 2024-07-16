#ifndef __menu_h
#define __menu_h

#include <stdint.h>
#include "../game_engine/game_engine.h"

#include "./locals/strings.h"

#define HAS_BITMAP      0x01
#define RIGHT_ALIGN     0x02
#define CENTER_ALIGN    0x04

#define MAX_MENU_ITEM_COUNT 256

#if (MAX_MENU_ITEM_COUNT <= 256)
	typedef uint8_t MENU_INDEX;
#else
	typedef uint16_t MENU_INDEX;
#endif

typedef struct s_Menu_Item
{
	void *bitmap;
	//unsigned char text[32];
	Strings text;
	void (*action)(void);
} Menu_Item;

typedef struct s_Menu
{
	uint8_t x;
	uint8_t y;
	uint8_t w;
	uint8_t visible_rows;
	
	uint8_t non_selected_text_color;
	uint8_t non_selected_bg_color;
	uint8_t selected_text_color;
	uint8_t selected_bg_color;
	
	uint8_t attrib;
	const GFXfont *font;

	MENU_INDEX capacity;
	MENU_INDEX selection;
	MENU_INDEX item_offset;	
	Menu_Item *items;
} Menu;

void menu_render(Menu *menu);
void menu_prev_item(Menu *menu);
void menu_next_item(Menu *menu);
void menu_select(Menu *menu);
Menu_Item *menu_get_item(Menu *menu, MENU_INDEX index);
Menu_Item *menu_get_current_item(Menu *menu);

#endif //__menu_h