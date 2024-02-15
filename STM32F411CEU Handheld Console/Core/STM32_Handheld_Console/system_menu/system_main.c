#include "./system_main.h"

#define SYSTEM_VER    "Alpha 4"

const char *system_ver = "Konsol Sistemi "SYSTEM_VER;

void system_main()
{
	init_display();
	clear_display();
	update_display();
	
	update_inputs();
	
	Menu system_menu = {
		.x = 10,
		.y = 60,
		.w = 220,
		.rows = 3,
		
		.non_selected_text_color = rgb888_to_rgb332(23, 139, 180),
		.non_selected_bg_color = rgb888_to_rgb332(23, 139, 180),
		.selected_text_color = rgb888_to_rgb332(105, 253, 255),
		.selected_bg_color = rgb888_to_rgb332(21, 72, 92),
		
		.items = {
			{ .bitmap = 0, .text = "Oyunlar", .action = system_list_games },
			{ .bitmap = 0, .text = "Ayarlar", .action = system_options },
			{ .bitmap = 0, .text = "Hakk"TR_i"nda", .action = system_about },
			0
		},
		.capacity = 3,
		.selection = 0,
		.item_offset = 0,
		
		.attrib = CENTER_ALIGN
	};
	
	while(1)
	{
		clear_display();
		set_text_area(0, 0, DISPLAY_WIDTH - 1, DISPLAY_HEIGHT - 1);
		
		int16_t tx, ty;
		uint16_t tw, th;
		text_bounds(system_ver, 0, 0, &tx, &ty, &tw, &th);
		set_cursor((DISPLAY_WIDTH - tw) / 2, get_font_height());
		set_text_color(0xff, 0xff);
		print_str(system_ver);
				
		set_cursor(0, DISPLAY_HEIGHT - 1);
		print_str(GP_Y""TR_O"nceki  "GP_X"Sonraki  "GP_A"Se"TR_c);

		menu_render(&system_menu);
		vm_execute();
		
		update_display();
		
		update_inputs();
		if(get_key_down(GAMEPAD_Y)) menu_prev_item(&system_menu);
		if(get_key_down(GAMEPAD_X)) menu_next_item(&system_menu);
		if(get_key_down(GAMEPAD_A)) menu_select(&system_menu);
	}
}

void system_list_games(void)
{
	show_error_window("Oyun Listesi", "Herhangi bir oyun bulunamad"TR_i".");
}

void system_options(void)
{
	show_error_window("Ayarlar", "Ayarlar men"TR_u"s"TR_u" hen"TR_u"z sisteme\neklenmemi"TR_s"tir.");
}

void system_about(void)
{
	show_info_window("Sistem Hakk"TR_i"nda", "Konsol Sistemi "SYSTEM_VER"\n\nCPU: ARM Cortex M4 @ 100 MHz\nRAM: 128 KB");
}