#include "./timer.h"

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