#include "./input_driver.h"

uint16_t current_keys = 0;
uint16_t previous_keys = 0;

//Joystick joysticks[2] = { 0 };

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
	previous_keys = current_keys;
	current_keys = get_input_status();
	disable_input();
}


#elif defined(__WIN32__)

#include <assert.h>

void update_inputs()
{
	previous_keys = current_keys;
	assert(0 && "WIN32 support for update_inputs() has not been implemented yet.");
}

#elif defined(__ANDROID__)

#else
	#error "Unsupported platform"
#endif // Platform Check
