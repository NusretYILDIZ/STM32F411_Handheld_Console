#include "./timer.h"

uint32_t elapsed_time;
uint32_t delta_time;

void wait_frame_time()
{
	int32_t sleep_time = FRAME_TIME - get_tick() + elapsed_time;
	if(sleep_time > 0) system_sleep(sleep_time);
	
	delta_time = get_tick() - elapsed_time;
	elapsed_time = get_tick();
}

#if defined(__arm__)

#include <stm32f4xx_hal.h>

void system_sleep(uint32_t time)
{
	HAL_Delay(time);
}

uint32_t get_tick()
{
	return HAL_GetTick();
}

#elif defined(__WIN32__)

#include "./win32/win32_sdl2_include.h"

void system_sleep(uint32_t time)
{
	Sleep(time);
}

uint32_t get_tick()
{
	return SDL_GetTicks();
}

#elif defined(__ANDROID__)

#endif