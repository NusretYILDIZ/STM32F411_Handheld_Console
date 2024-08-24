#include "./input_driver.h"

const uint16_t keys[15] = {
	GAMEPAD_DPAD_UP,
	GAMEPAD_DPAD_RIGHT,
	GAMEPAD_DPAD_DOWN,
	GAMEPAD_DPAD_LEFT,
	GAMEPAD_X,
	GAMEPAD_Y,
	GAMEPAD_A,
	GAMEPAD_B,
	GAMEPAD_SELECT,
	GAMEPAD_HOME,
	GAMEPAD_START,
	GAMEPAD_L1,
	GAMEPAD_R1,
	GAMEPAD_L2,
	GAMEPAD_R2,
};

uint16_t current_keys = 0;
uint16_t previous_keys = 0;

uint16_t key_held_frames[15];
uint16_t first_hold_time = 30;
uint16_t hold_interval = 1;

//Joystick joysticks[2] = { 0 };

void update_status()
{
	//printf("\nKey held timers\n");
	
	for(int key_index = 0; key_index < 15; key_index++)
	{
		//if(key == 0x0800) continue;  // Unused bit, skip.
		
		if(get_key_held(keys[key_index]))
		{
			key_held_frames[key_index]++;
		}
		else if(get_key_up(keys[key_index]))
		{
			key_held_frames[key_index] = 0;
		}
	}
}

uint8_t get_key(uint16_t key_code)
{
	return (current_keys & key_code);
}

uint8_t get_key_down(uint16_t key_code)
{
	return (!(previous_keys & key_code) && (current_keys & key_code));
}

uint8_t get_key_up(uint16_t key_code)
{
	return ((previous_keys & key_code) && !(current_keys & key_code));
}

uint8_t get_key_held(uint16_t key_code)
{
	return ((previous_keys & key_code) && (current_keys & key_code));
}

uint8_t get_key_held_for_time(uint16_t key_code)
{
	uint8_t result = 0;
	
	for(int key_index = 0; key_index < 15; key_index++)
	{
		if(keys[key_index] & key_code)
		{
			result &= (key_held_frames[key_index] == 1) || (key_held_frames[key_index] >= first_hold_time);
			if(key_held_frames[key_index] >= first_hold_time) key_held_frames[key_index] = first_hold_time - hold_interval;
			
			printf("%d, %d\n", key_index, result);
		}
	}
	printf("\n");
	
	return result;
}

/*
float get_joystick_x(uint8_t joystick)
{
	return (joystick == JOYSTICK_LEFT || joystick == JOYSTICK_RIGHT) ? joysticks[joystick].x : 0.0f;
}

float get_joystick_y(uint8_t joystick)
{
	return (joystick == JOYSTICK_LEFT || joystick == JOYSTICK_RIGHT) ? joysticks[joystick].y : 0.0f;
}
*/

#if defined(__arm__)

#include "./arm/stm32f411_input.h"

uint32_t gpioa_moder = 0;

void update_inputs()
{
	enable_input();
	HAL_Delay(1);
	previous_keys = current_keys;
	current_keys = get_input_status();
	disable_input();
	
	update_status();
}


#elif defined(__WIN32__)

#include <stdlib.h>
#include "./win32/win32_sdl2_include.h"


void update_inputs()
{
	SDL_Event input_event;
	previous_keys = current_keys;
	uint8_t first_handle = 1;
	
	while(SDL_PollEvent(&input_event))
	{
		switch(input_event.type)
		{
		case SDL_QUIT:
			SDL_Quit();
			exit(0);
			break;
		
		case SDL_KEYDOWN:
		case SDL_KEYUP:
			if(first_handle)
			{
				first_handle = 0;
				current_keys = 0;
			}
		
			if(input_event.key.state == SDL_PRESSED)
			{
				switch(input_event.key.keysym.sym)
				{
				case SDLK_w:
					current_keys |= GAMEPAD_DPAD_UP;
					break;
				
				case SDLK_d:
					current_keys |= GAMEPAD_DPAD_RIGHT;
					break;
				
				case SDLK_s:
					current_keys |= GAMEPAD_DPAD_DOWN;
					break;
				
				case SDLK_a:
					current_keys |= GAMEPAD_DPAD_LEFT;
					break;
				
				case SDLK_j:
					current_keys |= GAMEPAD_X;
					break;
				
				case SDLK_i:
					current_keys |= GAMEPAD_Y;
					break;
				
				case SDLK_k:
					current_keys |= GAMEPAD_A;
					break;
				
				case SDLK_l:
					current_keys |= GAMEPAD_B;
					break;
				
				case SDLK_b:
					current_keys |= GAMEPAD_SELECT;
					break;
				
				case SDLK_v:
					current_keys |= GAMEPAD_HOME;
					break;
				
				case SDLK_n:
					current_keys |= GAMEPAD_START;
					break;
				
				case SDLK_2:
					current_keys |= GAMEPAD_L1;
					break;
				
				case SDLK_8:
					current_keys |= GAMEPAD_R1;
					break;
				
				case SDLK_3:
					current_keys |= GAMEPAD_L2;
					break;
				
				case SDLK_9:
					current_keys |= GAMEPAD_R2;
					break;
				}
	
			//printf("prev: %4x, curr: %4x\n", previous_keys, current_keys);
			}
			break;
		}
	}
	
	update_status();
}

#elif defined(__ANDROID__)

#else
	#error "Unsupported platform"
#endif // Platform Check
