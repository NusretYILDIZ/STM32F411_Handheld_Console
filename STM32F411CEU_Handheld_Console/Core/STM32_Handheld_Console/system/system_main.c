#include "./system_main.h"

#include "./images/images.h"
#include "./system_menu.h"
#include "./settings.h"
#include "./internal_programs.h"

#include "./locals/locals.h"
#include "../display/YILDIZsoft_5x7.h"
#include "../file_system/file_system.h"

#include <string.h>

#define SYSTEM_VER    "Alpha 5"

#define GAME_LIST_ADDR  (sizeof(MENU) * 2 + sizeof(MENU_DATA))

const char *system_ver = "Konsol Sistemi "SYSTEM_VER;
//char **current_lang = strings_en;

SYSTEM_SETTINGS system_settings = {
	.current_lang = LANG_TR,
	.screen_brightness = 255,
	.theme_color = rgb888_to_rgb332(50, 50, 255),
	.username = "NusretY_Official"
};

void apply_lang(LANG lang)
{
	current_lang = langs[lang];
}

void change_lang(void)
{
	if(system_settings.current_lang == LANG_EN)
	{
		system_settings.current_lang = LANG_TR;
	}
	else
	{
		system_settings.current_lang = LANG_EN;
	}
	
	apply_lang(system_settings.current_lang);
}

void game_list()
{
	fill_display(system_settings.theme_color);
	set_cursor(5, 10);
	print_str(get_str(STR_GAME_LIST_TITLE));
	set_cursor(5, 50);
	print_str(get_str(STR_SEARCHING_FOR_GAMES));
	update_display();
	
	uint8_t games_count = get_games_list(GAME_LIST_ADDR);
	
	if(!games_count)
	{
		show_error_window(get_str(STR_GAME_CORRUPTED_TITLE), get_str(STR_GAME_CORRUPTED_MSG));
	}
	else
	{
		MENU *game_list_menu = (MENU *)(&ram[sizeof(MENU)]);
		MENU_DATA *game_list_menu_data = (MENU_DATA *)(&ram[sizeof(MENU) * 2]);
		game_list_menu_data->x = 10;
		game_list_menu_data->y = 60;
		game_list_menu_data->w = 220;
		game_list_menu_data->visible_rows = 8;
		game_list_menu_data->non_selected_text_color = rgb888_to_rgb332(23, 139, 180);
		game_list_menu_data->non_selected_bg_color = system_settings.theme_color;
		game_list_menu_data->selected_text_color = rgb888_to_rgb332(105, 253, 255);
		game_list_menu_data->selected_bg_color = rgb888_to_rgb332(21, 72, 92);
		game_list_menu_data->attrib = 0;
		game_list_menu_data->font = &YILDIZsoft_5x7;
		game_list_menu_data->capacity = games_count;
		game_list_menu_data->items = (MENU_ITEM *)(&ram[GAME_LIST_ADDR]);
		game_list_menu->selection = 0;
		game_list_menu->item_offset = 0;
		game_list_menu->data = game_list_menu_data;
		
		for(;;)
		{
			fill_display(system_settings.theme_color);
			menu_render(game_list_menu);
			update_display();
			
			update_inputs();
			if(get_key_down(GAMEPAD_DPAD_UP)) menu_prev_item(game_list_menu);
			if(get_key_down(GAMEPAD_DPAD_DOWN)) menu_next_item(game_list_menu);
			if(get_key_down(GAMEPAD_A)) menu_select(game_list_menu);
			if(get_key_down(GAMEPAD_B)) return;
			
			system_sleep(20);
		}
	}
}

void show_boot_screen()
{
	draw_image(69, 29, 100, 100, boot_image, 0);
	update_display();
	system_sleep(2000);
	
	clear_display();
	update_display();
}

void first_setup()  // TODO: Create an actual first setup menu.
{
	file_append(DIR_ROOT FILE_SYSTEM_SETTINGS, &system_settings, sizeof(system_settings));
}

void fs_init_error()
{
	int16_t tx, ty;
	uint16_t tw, th;
	
	fill_display(system_settings.theme_color);
	set_text_area(9, 9 + get_font_height(), 230, 150);
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
	set_text_color(rgb888_to_rgb332(255, 255, 255), 0xff);
	
	set_font_helper(&YILDIZsoft_5x7);
	set_text_wrap(1);
	
	show_boot_screen();
	
	update_inputs();
	
	if(!fs_init()) fs_init_error();
	
	if(!file_exists(DIR_ROOT FILE_SYSTEM_SETTINGS)) first_setup();
	else file_full_read(DIR_ROOT FILE_SYSTEM_SETTINGS, &system_settings);
	
	apply_lang(system_settings.current_lang);
	
	vm_init();
	
	prg_counter = sizeof(ram) - sizeof(test_code);
	memcpy(&ram[prg_counter], test_code, sizeof(test_code));
	engine_settings.game_code_addr = prg_counter;
	
	game_engine_loop();
	
	MENU *system_menu = (MENU *)ram;
	//system_menu->x = 10;
	//system_menu->y = 60;
	//system_menu->w = 220;
	//system_menu->visible_rows = 5;
	//system_menu->non_selected_text_color = rgb888_to_rgb332(23, 139, 180);
	//system_menu->non_selected_bg_color = system_settings.theme_color;
	//system_menu->selected_text_color = rgb888_to_rgb332(105, 253, 255);
	//system_menu->selected_bg_color = rgb888_to_rgb332(21, 72, 92);
	//system_menu->attrib = CENTER_ALIGN;
	//system_menu->font = &YILDIZsoft_5x7;
	//system_menu->capacity = 5;
	system_menu->selection = 0;
	system_menu->item_offset = 0;
	//system_menu->items = system_menu_items;
	system_menu->data = &system_menu_data;
	
	for(;;)
	{
		fill_display(system_settings.theme_color);
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

void corrupted_game_error()
{
	show_error_window(get_str(STR_GAME_CORRUPTED_TITLE), get_str(STR_GAME_CORRUPTED_MSG));
}