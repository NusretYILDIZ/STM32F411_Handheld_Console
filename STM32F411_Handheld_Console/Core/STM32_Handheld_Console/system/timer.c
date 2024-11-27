/*
	MIT License

	Copyright (c) 2024 Nusret YILDIZ

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/

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