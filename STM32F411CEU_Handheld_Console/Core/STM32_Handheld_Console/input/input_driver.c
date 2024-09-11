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
int8_t axises[4];

uint16_t key_held_frames[15];
uint16_t first_hold_time = 10;
uint16_t hold_interval = 2;

//Joystick joysticks[2] = { 0 };

void update_status()
{
	for(int key_index = 0; key_index < 15; key_index++)
	{
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
	uint8_t result = 1;
	
	for(int key_index = 0; key_index < 15; key_index++)
	{
		if(keys[key_index] & key_code)
		{
			result &= (key_held_frames[key_index] >= first_hold_time);
			if(key_held_frames[key_index] >= first_hold_time) key_held_frames[key_index] = first_hold_time - hold_interval;
		}
	}
	
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

void init_inputs()
{
	previous_keys = 0;
	current_keys = 0;
}

void update_inputs()
{
	// TODO: Take input from UART over USB. Connect to a computer that has a gamepad and start reading. This will be exclusive for the devkit.
	
	
	// This is for hardware buttons
	/*enable_input();
	HAL_Delay(1);
	previous_keys = current_keys;
	current_keys = get_input_status();
	disable_input();*/
	
	update_status();
}


#elif defined(__WIN32__)

#include <stdlib.h>
#include <stdio.h>
#include "./win32/win32_sdl2_include.h"

SDL_Event event;
SDL_GameController *gamepad;

// All SDL gamepad codes taken from here: https://blog.rubenwardy.com/2023/01/24/using_sdl_gamecontroller/

SDL_GameController *find_gamepads()
{
	for(int i = 0; i < SDL_NumJoysticks(); i++)
	{
		if(SDL_IsGameController(i))
		{
			return SDL_GameControllerOpen(i);
		}
	}
	
	return 0;
}

void init_inputs()
{
	previous_keys = 0;
	current_keys = 0;
	
	gamepad = find_gamepads();
}

void update_inputs()
{
	previous_keys = current_keys;
	
	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
		case SDL_QUIT:
			SDL_Quit();
			exit(0);
			break;
		
		case SDL_KEYDOWN:
			switch(event.key.keysym.sym)
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
			break;
		
		case SDL_KEYUP:
			switch(event.key.keysym.sym)
			{
			case SDLK_w:
				current_keys &= ~GAMEPAD_DPAD_UP;
				break;
			
			case SDLK_d:
				current_keys &= ~GAMEPAD_DPAD_RIGHT;
				break;
			
			case SDLK_s:
				current_keys &= ~GAMEPAD_DPAD_DOWN;
				break;
			
			case SDLK_a:
				current_keys &= ~GAMEPAD_DPAD_LEFT;
				break;
			
			case SDLK_j:
				current_keys &= ~GAMEPAD_X;
				break;
			
			case SDLK_i:
				current_keys &= ~GAMEPAD_Y;
				break;
			
			case SDLK_k:
				current_keys &= ~GAMEPAD_A;
				break;
			
			case SDLK_l:
				current_keys &= ~GAMEPAD_B;
				break;
			
			case SDLK_b:
				current_keys &= ~GAMEPAD_SELECT;
				break;
			
			case SDLK_v:
				current_keys &= ~GAMEPAD_HOME;
				break;
			
			case SDLK_n:
				current_keys &= ~GAMEPAD_START;
				break;
			
			case SDLK_2:
				current_keys &= ~GAMEPAD_L1;
				break;
			
			case SDLK_8:
				current_keys &= ~GAMEPAD_R1;
				break;
			
			case SDLK_3:
				current_keys &= ~GAMEPAD_L2;
				break;
			
			case SDLK_9:
				current_keys &= ~GAMEPAD_R2;
				break;
			}
			break;
		
		case SDL_CONTROLLERDEVICEADDED:
			if(!gamepad) gamepad = SDL_GameControllerOpen(event.cdevice.which);
			break;
		
		case SDL_CONTROLLERDEVICEREMOVED:
			if(gamepad && event.cdevice.which == SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(gamepad)))
			{
				SDL_GameControllerClose(gamepad);
				gamepad = find_gamepads();
			}
			break;
		
		case SDL_CONTROLLERBUTTONDOWN:
			if(gamepad && event.cdevice.which == SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(gamepad)))
			{
				switch(event.cbutton.button)
				{
				case SDL_CONTROLLER_BUTTON_DPAD_UP:
					current_keys |= GAMEPAD_DPAD_UP;
					break;
				
				case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
					current_keys |= GAMEPAD_DPAD_RIGHT;
					break;
				
				case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
					current_keys |= GAMEPAD_DPAD_DOWN;
					break;
				
				case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
					current_keys |= GAMEPAD_DPAD_LEFT;
					break;
				
				case SDL_CONTROLLER_BUTTON_X:
					current_keys |= GAMEPAD_X;
					break;
				
				case SDL_CONTROLLER_BUTTON_Y:
					current_keys |= GAMEPAD_Y;
					break;
				
				case SDL_CONTROLLER_BUTTON_A:
					current_keys |= GAMEPAD_A;
					break;
				
				case SDL_CONTROLLER_BUTTON_B:
					current_keys |= GAMEPAD_B;
					break;
				
				case SDL_CONTROLLER_BUTTON_BACK:
					current_keys |= GAMEPAD_SELECT;
					break;
				
				//case SDL_CONTROLLER_BUTTON_GUIDE:
				case SDL_CONTROLLER_BUTTON_LEFTSTICK:
				case SDL_CONTROLLER_BUTTON_RIGHTSTICK:
					current_keys |= GAMEPAD_HOME;
					break;
				
				case SDL_CONTROLLER_BUTTON_START:
					current_keys |= GAMEPAD_START;
					break;
				
				case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:
					current_keys |= GAMEPAD_L1;
					break;
				
				case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
					current_keys |= GAMEPAD_R1;
					break;
				}
			}
			break;
		
		case SDL_CONTROLLERBUTTONUP:
			if(gamepad && event.cdevice.which == SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(gamepad)))
			{
				switch(event.cbutton.button)
				{
				case SDL_CONTROLLER_BUTTON_DPAD_UP:
					current_keys &= ~GAMEPAD_DPAD_UP;
					break;
				
				case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
					current_keys &= ~GAMEPAD_DPAD_RIGHT;
					break;
				
				case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
					current_keys &= ~GAMEPAD_DPAD_DOWN;
					break;
				
				case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
					current_keys &= ~GAMEPAD_DPAD_LEFT;
					break;
				
				case SDL_CONTROLLER_BUTTON_X:
					current_keys &= ~GAMEPAD_X;
					break;
				
				case SDL_CONTROLLER_BUTTON_Y:
					current_keys &= ~GAMEPAD_Y;
					break;
				
				case SDL_CONTROLLER_BUTTON_A:
					current_keys &= ~GAMEPAD_A;
					break;
				
				case SDL_CONTROLLER_BUTTON_B:
					current_keys &= ~GAMEPAD_B;
					break;
				
				case SDL_CONTROLLER_BUTTON_BACK:
					current_keys &= ~GAMEPAD_SELECT;
					break;
				
				//case SDL_CONTROLLER_BUTTON_GUIDE:
				case SDL_CONTROLLER_BUTTON_LEFTSTICK:
				case SDL_CONTROLLER_BUTTON_RIGHTSTICK:
					current_keys &= ~GAMEPAD_HOME;
					break;
				
				case SDL_CONTROLLER_BUTTON_START:
					current_keys &= ~GAMEPAD_START;
					break;
				
				case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:
					current_keys &= ~GAMEPAD_L1;
					break;
				
				case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
					current_keys &= ~GAMEPAD_R1;
					break;
				}
			}
			break;
		
		case SDL_CONTROLLERAXISMOTION:
			if(gamepad && event.cdevice.which == SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(gamepad)))
			{
				switch(event.caxis.axis)
				{
				case SDL_CONTROLLER_AXIS_LEFTX:
					axises[AXIS_LEFT_X] = event.caxis.value / 256;
					//printf("Normalized value = %d, ", axises[AXIS_LEFT_X]);
					//printf("Left X = ");
					break;
				
				case SDL_CONTROLLER_AXIS_LEFTY:
					axises[AXIS_LEFT_Y] = event.caxis.value / 256;
					//printf("Normalized value = %d, ", axises[AXIS_LEFT_Y]);
					//printf("Left Y = ");
					break;
				
				case SDL_CONTROLLER_AXIS_RIGHTX:
					axises[AXIS_RIGHT_X] = event.caxis.value / 256;
					//printf("Normalized value = %d, ", axises[AXIS_RIGHT_X]);
					//printf("Right X = ");
					break;
				
				case SDL_CONTROLLER_AXIS_RIGHTY:
					axises[AXIS_RIGHT_Y] = event.caxis.value / 256;
					//printf("Normalized value = %d, ", axises[AXIS_RIGHT_Y]);
					//printf("Right Y = ");
					break;
				
				case SDL_CONTROLLER_AXIS_TRIGGERLEFT:
					//printf("L2 = ");
					if(event.caxis.value > 0)
						current_keys |= GAMEPAD_L2;
					else
						current_keys &= ~GAMEPAD_L2;
					break;
				
				case SDL_CONTROLLER_AXIS_TRIGGERRIGHT:
					//printf("R2 = ");
					if(event.caxis.value > 0)
						current_keys |= GAMEPAD_R2;
					else
						current_keys &= ~GAMEPAD_R2;
					break;
				}
				//printf("%d\n", event.caxis.value);
			}
			break;
		}
	}
	
	update_status();
}

#elif defined(__ANDROID__)
	#error "Input driver for Android not implemented yet."
#else
	#error "Unsupported platform"
#endif // Platform Check
