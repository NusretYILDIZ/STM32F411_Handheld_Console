#include "./game_engine.h"

#include "../input/input_driver.h"

ENGINE_SETTINGS engine_settings;
uint32_t elapsed_time;

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
			printf("KERNEL_PANIC: ");
			
			switch(panic_code)
			{
			case PANIC_NONE:
				printf("PANIC_NONE");
				break;
			
			case PANIC_UNKNOWN_DATA_TYPE:
				printf("PANIC_UNKNOWN_DATA_TYPE");
				break;
			
			case PANIC_UNKNOWN_ADDR_MODE:
				printf("PANIC_UNKNOWN_ADDR_MODE");
				break;
			
			case PANIC_INVALID_INSTRUCTION:
				printf("PANIC_INVALID_INSTRUCTION");
				break;
			
			case PANIC_DATA_TYPE_DISCREPANCY:
				printf("PANIC_DATA_TYPE_DISCREPANCY");
				break;
			
			default:
				printf("UNKNOWN");
				break;
			}
			printf("\nProgram counter: %d\n", prg_counter - engine_settings.game_code_addr);
			
			for(;;);
			
			return -1;
		}
		
		// Render functions
		update_display();
		wait_frame_time();
		status_flag &= ~END_OF_LOOP_FLAG;
	}
	
	return 0;
}