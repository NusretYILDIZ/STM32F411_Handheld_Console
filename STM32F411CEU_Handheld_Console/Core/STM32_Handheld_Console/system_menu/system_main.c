#include "./system_main.h"

#define SYSTEM_VER    "Alpha 4"

const char *system_ver = "Konsol Sistemi "SYSTEM_VER;

const unsigned char image[32][32] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x32, 0x37, 0x37, 0x37, 0x37, 0x2e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x33, 0x37, 0x37, 0x57, 0x57, 0x2e, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x33, 0x37, 0x37, 0x37, 0x37, 0x37, 0x2e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x33, 0x37, 0x37, 0x37, 0x37, 0x37, 0x2e, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x2e, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x2e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2e, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x2e, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x2e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x2e, 0x00, 0x24, 0x24, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x29, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x2e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x33, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x2e, 0x20, 0x25, 0x24, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x2e, 0x37, 0x37, 0x37, 0x37, 0x37, 0x33, 0x37, 0x29, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2a, 0x33, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x2e, 0x00, 0x24, 0x04, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x2e, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x2a, 0x00, 0x00, 0x00, 0x00, 0x05, 0x33, 0x33, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x33, 0x2a, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x2e, 0x37, 0x37, 0x37, 0x33, 0x33, 0x37, 0x33, 0x2e, 0x00, 0x00, 0x00, 0x00, 0x33, 0x37, 0x33, 0x37, 0x37, 0x37, 0x37, 0x33, 0x57, 0x53, 0x2e, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x2e, 0x37, 0x33, 0x33, 0x33, 0x37, 0x37, 0x33, 0x2e, 0x00, 0x00, 0x00, 0x2e, 0x57, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x57, 0x57, 0x57, 0x2e, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x2a, 0x33, 0x33, 0x33, 0x37, 0x37, 0x37, 0x33, 0x2e, 0x00, 0x00, 0x05, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x57, 0x57, 0x57, 0x2e, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x04, 0x2e, 0x2e, 0x33, 0x33, 0x37, 0x37, 0x37, 0x37, 0x37, 0x33, 0x2e, 0x00, 0x00, 0x33, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x33, 0x57, 0x37, 0x33, 0x2e, 0x2a, 0x2e, 0x2e, 0x2e, 
0x00, 0x29, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x33, 0x33, 0x29, 0x00, 0x2a, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x33, 0x33, 0x37, 0x33, 0x33, 0x33, 0x53, 0x33, 0x57, 0x57, 0x33, 
0x00, 0x2e, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x33, 0x33, 0x2e, 0x2a, 0x25, 0x05, 0x2f, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x4f, 0x53, 0x33, 0x2f, 0x2f, 0x33, 0x33, 0x53, 0x53, 0x53, 0x2e, 
0x00, 0x33, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x33, 0x33, 0x05, 0x00, 0x00, 0x2a, 0x2f, 0x33, 0x33, 0x2f, 0x2f, 0x2f, 0x53, 0x53, 0x33, 0x33, 0x2f, 0x2f, 0x33, 0x53, 0x53, 0x53, 0x57, 0x29, 
0x00, 0x33, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x33, 0x2a, 0x05, 0x2a, 0x2e, 0x2e, 0x2e, 0x2f, 0x2f, 0x2f, 0x2e, 0x2e, 0x4f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x33, 0x53, 0x57, 0x57, 0x24, 
0x29, 0x37, 0x37, 0x37, 0x37, 0x37, 0x33, 0x33, 0x2f, 0x2f, 0x2f, 0x2e, 0x2f, 0x2e, 0x2e, 0x2f, 0x33, 0x2f, 0x2f, 0x2f, 0x2e, 0x2e, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x33, 0x33, 0x2e, 0x00, 
0x2e, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x33, 0x2f, 0x33, 0x33, 0x33, 0x2f, 0x33, 0x33, 0x33, 0x33, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2a, 0x00, 
0x32, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x37, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x2f, 0x2f, 0x2f, 0x2f, 0x53, 0x4f, 0x4f, 0x2e, 0x2e, 0x4e, 0x25, 0x00, 
0x04, 0x00, 0x00, 0x00, 0x2e, 0x37, 0x37, 0x37, 0x37, 0x33, 0x33, 0x37, 0x33, 0x33, 0x33, 0x33, 0x33, 0x53, 0x33, 0x33, 0x33, 0x2e, 0x2f, 0x33, 0x53, 0x53, 0x33, 0x2a, 0x00, 0x04, 0x04, 0x24, 
0x00, 0x00, 0x00, 0x00, 0x2e, 0x37, 0x37, 0x37, 0x37, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x37, 0x37, 0x37, 0x37, 0x33, 0x05, 0x33, 0x33, 0x53, 0x33, 0x53, 0x2e, 0x00, 0x00, 0x04, 0x04, 
0x00, 0x00, 0x00, 0x00, 0x2e, 0x37, 0x37, 0x37, 0x37, 0x37, 0x33, 0x33, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x29, 0x00, 0x33, 0x33, 0x33, 0x33, 0x33, 0x2e, 0x00, 0x04, 0x24, 0x24, 
0x00, 0x00, 0x00, 0x00, 0x09, 0x37, 0x37, 0x33, 0x33, 0x33, 0x33, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x2e, 0x00, 0x05, 0x33, 0x33, 0x33, 0x33, 0x33, 0x2e, 0x20, 0x24, 0x25, 0x24, 
0x00, 0x00, 0x00, 0x00, 0x04, 0x33, 0x2f, 0x2f, 0x33, 0x33, 0x33, 0x33, 0x37, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x00, 0x00, 0x25, 0x33, 0x33, 0x33, 0x33, 0x53, 0x2e, 0x24, 0x25, 0x25, 0x24, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x2e, 0x33, 0x2f, 0x2f, 0x2f, 0x33, 0x33, 0x57, 0x33, 0x33, 0x33, 0x33, 0x33, 0x29, 0x00, 0x00, 0x25, 0x2f, 0x2f, 0x2f, 0x2f, 0x4f, 0x2a, 0x24, 0x25, 0x25, 0x24, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x29, 0x33, 0x2f, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x2e, 0x00, 0x00, 0x00, 0x04, 0x2f, 0x2f, 0x2e, 0x2e, 0x4e, 0x29, 0x24, 0x24, 0x25, 0x24, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2f, 0x33, 0x33, 0x33, 0x2f, 0x33, 0x2f, 0x2f, 0x33, 0x33, 0x2f, 0x00, 0x00, 0x00, 0x00, 0x04, 0x2e, 0x2e, 0x2a, 0x2a, 0x2e, 0x29, 0x00, 0x04, 0x24, 0x24, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x2f, 0x2e, 0x2e, 0x25, 0x00, 0x00, 0x00, 0x00, 0x04, 0x2e, 0x2e, 0x4e, 0x4e, 0x4e, 0x29, 0x00, 0x04, 0x24, 0x24, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x29, 0x29, 0x29, 0x29, 0x29, 0x25, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x25, 0x25, 0x29, 0x29, 0x25, 0x00, 0x00, 0x04, 0x24, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const unsigned char prg[] = {
	0x01, TYPE_INT8 | ADDR_ABS, 0x09, 0x00, 0x00, 0x00, TYPE_INT8 | ADDR_IMM, 36,
	0x02, TYPE_INT8 | ADDR_ABS, 0x09, 0x00, 0x00, 0x00, TYPE_INT8 | ADDR_ABS, 0x09, 0x00, 0x00, 0x00, TYPE_INT8 | ADDR_IMM | ARITH_ADD, 4, TYPE_INT8 | ADDR_IMM | ARITH_DIV, 10, TYPE_TERMINATE
};

void vm_message(void)
{
	char msg[20];
	snprintf(msg, sizeof(msg), "$0x00000009: %3d", ram[9]);
	show_info_window("Virtual Machine", msg);
}

//#if defined(__arm__)

uint8_t system_main()
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
	
	memcpy(ram + 50, prg, sizeof(prg));
	prg_counter = 50;
	
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
		
		set_cursor(0, DISPLAY_HEIGHT - 3 * get_font_height());
		printf_str("Program counter: %d\n$0x00000009: %3d", prg_counter, ram[9]);
		char txt[50];
		snprintf(txt, sizeof(txt), "Program counter: %d\n$0x00000009: %3d", prg_counter, ram[9]);
		show_info_window("Virtual Machine", txt);

		menu_render(&system_menu);
		
		draw_image(-10, -5, 32, 32, image, 0);
		draw_image(220, 135, 32, 32, image, 0);

		update_display();
		
		vm_execute();
		
		update_inputs();
		/*if(get_key_down(GAMEPAD_SELECT))
		{
			vm_execute();
			vm_message();
		}*/
		if(get_key_down(GAMEPAD_Y)) menu_prev_item(&system_menu);
		if(get_key_down(GAMEPAD_X)) menu_next_item(&system_menu);
		if(get_key_down(GAMEPAD_A)) menu_select(&system_menu);
	}
	
	return 0;
}

/*#elif defined(__WIN32__)

uint8_t system_main()
{
	return init_display();
}

#endif*/

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