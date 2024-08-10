#ifndef __menu_h
#define __menu_h

#include <stdint.h>
#include "../game_engine/game_engine.h"

#include "./locals/strings.h"

#define HAS_BITMAP      0x01
#define RIGHT_ALIGN     0x02
#define CENTER_ALIGN    0x04
#define SYSTEM_MENU     0x08

#define MAX_MENU_ITEM_COUNT 256
#define MAX_MENU_TEXT_LENGTH 64

#if (MAX_MENU_ITEM_COUNT <= 256)
	typedef uint8_t MENU_INDEX;
#else
	typedef uint16_t MENU_INDEX;
#endif

typedef union u_MENU_TEXT
{
	String string;
	char text[MAX_MENU_TEXT_LENGTH];
} MENU_TEXT;

typedef struct s_MENU_ITEM
{
	void *bitmap;
	//unsigned char text[MAX_MENU_TEXT_LENGTH];
	//String text;
	MENU_TEXT menu_text;
	void (*action)(void);
} MENU_ITEM;

typedef struct s_MENU_DATA
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
	//MENU_INDEX selection;
	//MENU_INDEX item_offset;	
	MENU_ITEM *items;
} MENU_DATA;

typedef struct s_MENU
{
	MENU_INDEX selection;
	MENU_INDEX item_offset;
	MENU_DATA *data;
} MENU;

void menu_render(MENU *menu);
void menu_prev_item(MENU *menu);
void menu_next_item(MENU *menu);
void menu_select(MENU *menu);
MENU_ITEM *menu_get_item(MENU *menu, MENU_INDEX index);
MENU_ITEM *menu_get_current_item(MENU *menu);

#endif //__menu_h