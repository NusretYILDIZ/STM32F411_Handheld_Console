#ifndef __menu_h
#define __menu_h

#include <stdint.h>

#define MAX_MENU_ITEM_COUNT 128

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
	
	uint8_t bg_color;
	uint8_t non_selected_text_color;
	uint8_t selected_text_color;
	uint8_t selection_bg_color;
	
	Menu_Item items[MAX_MENU_ITEM_COUNT];
	uint16_t capacity;
	uint16_t selection;
	uint16_t item_shift;
} Menu;

void menu_render(Menu *menu);
void menu_go_up(Menu *menu);
void menu_go_down(Menu *menu);
void menu_select(Menu *menu);

#endif //__menu_h