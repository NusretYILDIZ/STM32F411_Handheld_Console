#include "./game_engine.h"

#include "../input/input_driver.h"
#include "../system/locals/strings.h"

const char *panic_code_names[] = {
	PANIC_CODES(PANIC_NAMES)
};

ENGINE_SETTINGS engine_settings;
uint32_t elapsed_time;

void kernel_panic_screen()
{
	fill_display(0xE0);
	set_text_area(10, 10 + get_font_height(), 229, 159);
	set_cursor(10, 50);
	printf_str("%s%s", get_str(STR_KERNEL_PANIC_MSG), panic_code_names[panic_code]);
	
	set_cursor(10, 156);
	printf_str(GP_HOME "%s", get_str(STR_BACK));
	update_display();
	
	for(;;)
	{
		update_inputs();
		if(get_key_down(GAMEPAD_HOME)) return;
	}
}

void wait_frame_time()
{
	while(get_tick() - elapsed_time < 33);
	elapsed_time = get_tick();
}

void load_game(void *game)
{
	engine_settings = (ENGINE_SETTINGS) { 0 };
}

uint8_t game_engine_loop(void)
{
	while(!(status_flag & EXIT_GAME_FLAG))
	{
		update_inputs();
		vm_run();
		
		if(status_flag & KERNEL_PANIC_FLAG)
		{
			// Panic here.
			// TODO: Implement a panic screen.
			printf("KERNEL_PANIC: %s", panic_code_names[panic_code]);
			printf("\nProgram counter: %d\n", prg_counter - engine_settings.game_code_addr);
			
			kernel_panic_screen();
			
			return -1;
		}
		
		// Render functions
		update_display();
		wait_frame_time();
		status_flag &= ~END_OF_LOOP_FLAG;
	}
	
	return 0;
}