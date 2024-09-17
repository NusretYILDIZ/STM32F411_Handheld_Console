#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "../sdl2/include/SDL2/SDL.h"
#include "../../STM32F411_Handheld_Console/Core/STM32_Handheld_Console/input/input_driver.h"

char port_name[11];

void fatal_error(const char *msg)
{
	fprintf(stderr, "%s\n", msg);
	system("pause");
	exit(-1);
}

int main(int argc, char **argv)
{
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		printf("SDL_Init failed: %s\n", SDL_GetError());
		system("pause");
		exit(-1);
	}
	
	init_inputs();
	
	printf("\n Gamepad Input Server for STM32F411 Handheld Console\n\nEnter port number: COM");
	
	char port_no[4] = { '\0' };
	fgets(port_no, 3, stdin);
	
	size_t str_len = strlen(port_no);
	
	for(int i = 0; i < str_len; i++)
	{
		if(port_no[i] == '\n') port_no[i] = '\0';
	}
	
	snprintf(port_name, sizeof(port_name), "\\\\.\\COM%s", port_no);
	
	HANDLE h_serial = CreateFile(port_name, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	
	printf("\nOpening port %s...\n\n", port_name);
	
	if(h_serial == INVALID_HANDLE_VALUE)
	{
		fatal_error("Cannot open specified port.");
	}
	
	printf("Port %s opened successfully.\n\n", port_name);
	
	DCB dcb_serial_params = { 0 };
	dcb_serial_params.DCBlength = sizeof(DCB);
	
	if(!GetCommState(h_serial, &dcb_serial_params))
	{
		fatal_error("Error while GetCommState()");
	}
	
	dcb_serial_params.BaudRate = CBR_115200;
	dcb_serial_params.ByteSize = 8;
	dcb_serial_params.StopBits = ONESTOPBIT;
	dcb_serial_params.Parity = NOPARITY;
	
	if(!SetCommState(h_serial, &dcb_serial_params))
	{
		fatal_error("Error while SetCommState()");
	}
	
	COMMTIMEOUTS timeouts = { 0 };
	timeouts.ReadIntervalTimeout = 50;
	timeouts.ReadTotalTimeoutConstant = 50;
	timeouts.ReadTotalTimeoutMultiplier = 10;
	timeouts.WriteTotalTimeoutConstant = 50;
	timeouts.WriteTotalTimeoutMultiplier = 10;
	
	if(!SetCommTimeouts(h_serial, &timeouts))
	{
		fatal_error("Error while SetCommTimeouts()");
	}
	
	printf("Server is running.\n\n");
	
	for(;;)
	{
		char rx_buf[2] = { '\0' };
		DWORD rx_read_count = 0;
		DWORD tx_write_count = 0;
		
		if(!ReadFile(h_serial, rx_buf, 1, &rx_read_count, 0))
		{
			CloseHandle(h_serial);
			fatal_error("Error while ReadFile()");
		}
		
		uint8_t tx_buf[6] = { 0 };
		
		if(rx_buf[0] == 'u')
		{
			printf("Update request from client. ");
			
			update_inputs();
			
			*(uint16_t *)tx_buf = current_keys;
			*(int8_t *)(tx_buf + 2) = axises[0];
			*(int8_t *)(tx_buf + 3) = axises[1];
			*(int8_t *)(tx_buf + 4) = axises[2];
			*(int8_t *)(tx_buf + 5) = axises[3];
			
			printf("Updated inputs: 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x\n", tx_buf[0], tx_buf[1], tx_buf[2], tx_buf[3], tx_buf[4], tx_buf[5]);
			
			if(!WriteFile(h_serial, tx_buf, 6, &tx_write_count, 0))
			{
				CloseHandle(h_serial);
				fatal_error("Error while WriteFile()");
			}
		}
	}
	
	system("pause");
	
	return 0;
}