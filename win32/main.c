#include <stdint.h>
#include <stdio.h>
#include "./sdl2/include/SDL2/SDL.h"
#include "../STM32F411CEU Handheld Console/Core/STM32_Handheld_Console/STM32_Handheld_Console.h"

int main(int argc, char **argv)
{
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		printf("SDL_Init failed: %s\n", SDL_GetError());
		return 1;
	}
	
	uint8_t res = system_main();
	
	//SDL_Quit();
	
	return res;
}