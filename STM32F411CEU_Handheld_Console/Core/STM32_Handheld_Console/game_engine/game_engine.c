#include "./game_engine.h"

#include "../input/input_driver.h"

void wait_frame_time()
{
	while(get_tick() - elapsed_time < 33);
	elapsed_time = get_tick();
}

void load_game(void *game)
{
	engine_settings = 0;
}

uint8_t game_engine_loop()
{
	update_inputs();
	vm_run();
	
	// Render functions
	update_display();
	
	wait_frame_time();
}