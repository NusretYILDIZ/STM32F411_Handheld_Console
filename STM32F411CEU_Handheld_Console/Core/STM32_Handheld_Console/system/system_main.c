#include "./system_main.h"

#include "./images/images.h"
#include "./system_menu.h"
#include "./settings.h"

#include "./locals/locals.h"
#include "../display/YILDIZsoft_5x7.h"
#include "../file_system/file_system.h"

#define SYSTEM_VER    "Alpha 5"

const char *system_ver = "Konsol Sistemi "SYSTEM_VER;

SYSTEM_SETTINGS system_settings = {
	.current_lang = strings_en,
	.screen_brightness = 255,
	.theme_color = rgb888_to_rgb332(50, 150, 255),
	//.username = { '\0' }
};

void change_lang(void)
{
	if(system_settings.current_lang == strings_en) system_settings.current_lang = strings_tr;
	else system_settings.current_lang = strings_en;
}

void show_boot_screen()
{
	draw_image(69, 29, 100, 100, boot_image, 0);
	update_display();
	system_sleep(2000);
	
	clear_display();
	update_display();
}

void fs_init_error()
{
	int16_t tx, ty;
	uint16_t tw, th;
	
	fill_display(system_settings.theme_color);
	set_text_area(9, 9, 230, 150);
	set_text_color(rgb888_to_rgb332(255, 255, 255), 0xff);
	
	text_bounds(get_str(STR_INIT_FS_ERROR), 9, 9, &tx, &ty, &tw, &th);
	set_cursor((DISPLAY_WIDTH - tw) / 2, (DISPLAY_HEIGHT - th) / 2);
	print_str(get_str(STR_INIT_FS_ERROR));
	update_display();
	
	for(;;)
	{
		update_inputs();
		system_sleep(100);
	}
}

uint8_t system_main()
{
	//current_lang = strings_tr;
	
	init_display();
	clear_display();
	update_display();
	
	set_font_helper(&YILDIZsoft_5x7);
	set_text_wrap(1);
	
	show_boot_screen();
	
	update_inputs();
	
	if(!fs_init()) fs_init_error();
	
	vm_init();
	
	Menu *system_menu = (Menu *)ram;
	system_menu->x = 10;
	system_menu->y = 60;
	system_menu->w = 220;
	system_menu->visible_rows = 5;
	system_menu->non_selected_text_color = rgb888_to_rgb332(23, 139, 180);
	system_menu->non_selected_bg_color = rgb888_to_rgb332(23, 139, 180);
	system_menu->selected_text_color = rgb888_to_rgb332(105, 253, 255);
	system_menu->selected_bg_color = rgb888_to_rgb332(21, 72, 92);
	system_menu->attrib = CENTER_ALIGN;
	system_menu->font = &YILDIZsoft_5x7;
	system_menu->capacity = 5;
	system_menu->selection = 0;
	system_menu->item_offset = 0;
	system_menu->items = system_menu_items;
	
	for(;;)
	{
		clear_display();
		menu_render(system_menu);
		update_display();
		
		update_inputs();
		if(get_key_down(GAMEPAD_DPAD_UP)) menu_prev_item(system_menu);
		if(get_key_down(GAMEPAD_DPAD_DOWN)) menu_next_item(system_menu);
		if(get_key_down(GAMEPAD_A)) menu_select(system_menu);
		
		system_sleep(20);
	}
	
	return 0;
}