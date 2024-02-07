#ifndef __menu_h
#define __menu_h

#include <stdint.h>

#define HAS_BITMAP      0x01
#define RIGHT_ALIGN     0x02
#define CENTER_ALIGN    0x04

#define MAX_MENU_ITEM_COUNT 256

#if (MAX_MENU_ITEM_COUNT <= 256)
	typedef uint8_t Menu_Index;
#else
	typedef uint16_t Menu_Index;
#endif

typedef struct Menu_Item
{
	void *bitmap;
	unsigned char text[32];
	void (*action)(void);
} Menu_Item;

typedef struct Menu
{
	int16_t x;
	int16_t y;
	uint16_t w;
	uint8_t rows;
	
	uint8_t non_selected_text_color;
	uint8_t non_selected_bg_color;
	uint8_t selected_text_color;
	uint8_t selected_bg_color;
	
	Menu_Item items[MAX_MENU_ITEM_COUNT];
	Menu_Index capacity;
	Menu_Index selection;
	Menu_Index item_offset;
	
	uint8_t attrib;
} Menu;

void menu_render(Menu *menu);
void menu_prev_item(Menu *menu);
void menu_next_item(Menu *menu);
void menu_select(Menu *menu);

#endif //__menu_h