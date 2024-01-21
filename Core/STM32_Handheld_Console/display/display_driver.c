#include "./display_driver.h"

#include <stdarg.h>
#include <string.h>

uint8_t vram[DISPLAY_WIDTH][DISPLAY_HEIGHT] = { 0 };

// Taken from: https://blog.frankvh.com/2015/03/29/fast-rgb332-to-rgb565-colorspace-conversion/

// This look-up table causes bugged binary with STM32 compiler
const uint16_t rgb332_to_rgb565[256] = {
    0x0000, 0x000a, 0x0015, 0x001f, 0x0120, 0x012a, 0x0135, 0x013f, 
    0x0240, 0x024a, 0x0255, 0x025f, 0x0360, 0x036a, 0x0375, 0x037f, 
    0x0480, 0x048a, 0x0495, 0x049f, 0x05a0, 0x05aa, 0x05b5, 0x05bf, 
    0x06c0, 0x06ca, 0x06d5, 0x06df, 0x07e0, 0x07ea, 0x07f5, 0x07ff, 
    0x2000, 0x200a, 0x2015, 0x201f, 0x2120, 0x212a, 0x2135, 0x213f, 
    0x2240, 0x224a, 0x2255, 0x225f, 0x2360, 0x236a, 0x2375, 0x237f, 
    0x2480, 0x248a, 0x2495, 0x249f, 0x25a0, 0x25aa, 0x25b5, 0x25bf, 
    0x26c0, 0x26ca, 0x26d5, 0x26df, 0x27e0, 0x27ea, 0x27f5, 0x27ff, 
    0x4800, 0x480a, 0x4815, 0x481f, 0x4920, 0x492a, 0x4935, 0x493f, 
    0x4a40, 0x4a4a, 0x4a55, 0x4a5f, 0x4b60, 0x4b6a, 0x4b75, 0x4b7f, 
    0x4c80, 0x4c8a, 0x4c95, 0x4c9f, 0x4da0, 0x4daa, 0x4db5, 0x4dbf, 
    0x4ec0, 0x4eca, 0x4ed5, 0x4edf, 0x4fe0, 0x4fea, 0x4ff5, 0x4fff, 
    0x6800, 0x680a, 0x6815, 0x681f, 0x6920, 0x692a, 0x6935, 0x693f, 
    0x6a40, 0x6a4a, 0x6a55, 0x6a5f, 0x6b60, 0x6b6a, 0x6b75, 0x6b7f, 
    0x6c80, 0x6c8a, 0x6c95, 0x6c9f, 0x6da0, 0x6daa, 0x6db5, 0x6dbf, 
    0x6ec0, 0x6eca, 0x6ed5, 0x6edf, 0x6fe0, 0x6fea, 0x6ff5, 0x6fff, 
    0x9000, 0x900a, 0x9015, 0x901f, 0x9120, 0x912a, 0x9135, 0x913f, 
    0x9240, 0x924a, 0x9255, 0x925f, 0x9360, 0x936a, 0x9375, 0x937f, 
    0x9480, 0x948a, 0x9495, 0x949f, 0x95a0, 0x95aa, 0x95b5, 0x95bf, 
    0x96c0, 0x96ca, 0x96d5, 0x96df, 0x97e0, 0x97ea, 0x97f5, 0x97ff, 
    0xb000, 0xb00a, 0xb015, 0xb01f, 0xb120, 0xb12a, 0xb135, 0xb13f, 
    0xb240, 0xb24a, 0xb255, 0xb25f, 0xb360, 0xb36a, 0xb375, 0xb37f, 
    0xb480, 0xb48a, 0xb495, 0xb49f, 0xb5a0, 0xb5aa, 0xb5b5, 0xb5bf, 
    0xb6c0, 0xb6ca, 0xb6d5, 0xb6df, 0xb7e0, 0xb7ea, 0xb7f5, 0xb7ff, 
    0xd800, 0xd80a, 0xd815, 0xd81f, 0xd920, 0xd92a, 0xd935, 0xd93f, 
    0xda40, 0xda4a, 0xda55, 0xda5f, 0xdb60, 0xdb6a, 0xdb75, 0xdb7f, 
    0xdc80, 0xdc8a, 0xdc95, 0xdc9f, 0xdda0, 0xddaa, 0xddb5, 0xddbf, 
    0xdec0, 0xdeca, 0xded5, 0xdedf, 0xdfe0, 0xdfea, 0xdff5, 0xdfff, 
    0xf800, 0xf80a, 0xf815, 0xf81f, 0xf920, 0xf92a, 0xf935, 0xf93f, 
    0xfa40, 0xfa4a, 0xfa55, 0xfa5f, 0xfb60, 0xfb6a, 0xfb75, 0xfb7f, 
    0xfc80, 0xfc8a, 0xfc95, 0xfc9f, 0xfda0, 0xfdaa, 0xfdb5, 0xfdbf, 
    0xfec0, 0xfeca, 0xfed5, 0xfedf, 0xffe0, 0xffea, 0xfff5, 0xffff 
};

// Taken from: https://blog.frankvh.com/2015/03/29/fast-rgb332-to-rgb565-colorspace-conversion/
/*const unsigned char b3to6lookup[8] = { 0, 9, 18, 27, 36, 45, 54, 63 };
const unsigned char b3to5lookup[8] = { 0, 4, 9, 13, 18, 22, 27, 31 };
const unsigned char b2to5lookup[4] = { 0, 10, 21, 31 };

// Taken from: https://blog.frankvh.com/2015/03/29/fast-rgb332-to-rgb565-colorspace-conversion/
uint16_t ConvertRGB332toRGB565(unsigned char rgb332)
{
	uint16_t red, green, blue;

	red = (rgb332 & 0xe0) >> 5;		// rgb332 3 red bits now right justified
	red = (uint16_t)b3to5lookup[red];		// 3 bits converted to 5 bits
	red = red << 11;			// red bits now 5 MSB bits

	green = (rgb332 & 0x1c) >> 2;		// rgb332 3 green bits now right justified
	green = (uint16_t)b3to6lookup[green];	// 3 bits converted to 6 bits
	green = green << 5;			// green bits now 6 "middle" bits

	blue = rgb332 & 0x03;			// rgb332 2 blue bits are right justified
	blue = (uint16_t)b2to5lookup[blue];	// 2 bits converted to 5 bits, right justified

	return (uint16_t)(red | green | blue);
}*/

void draw_pixel(int16_t x, int16_t y, uint8_t color)
{
	if(x < 0 || x >= DISPLAY_WIDTH || y < 0 || y >= DISPLAY_HEIGHT) return;
	
	//vram[y * DISPLAY_WIDTH + x] = color;
	vram[x][y] = color;
}

void draw_v_line(int16_t x, int16_t y, int16_t h, uint8_t color)
{
	// Boundary Checks And Corrections
	if(x < 0 || x >= DISPLAY_WIDTH || y >= DISPLAY_HEIGHT) return;
	if(y < 0) { h += y;  y = 0; }
	if(y + h > DISPLAY_HEIGHT) h = DISPLAY_HEIGHT - y;
	if(h < 1) return;
	
	while(h)
	{
		//vram[(y + h) * DISPLAY_WIDTH + x] = color;
		vram[x][(y + h - 1)] = color;
		--h;
	}
}

void draw_h_line(int16_t x, int16_t y, int16_t w, uint8_t color)
{
	// Boundary Checks And Corrections
	if(x >= DISPLAY_WIDTH || y < 0 || y >= DISPLAY_HEIGHT) return;
	if(x < 0) { w += x;  x = 0; }
	if(x + w > DISPLAY_WIDTH) w = DISPLAY_WIDTH - x;
	if(w < 1) return;
	
	while(w)
	{
		//vram[y * DISPLAY_WIDTH + (x + w - 1)] = color;
		vram[(x + w - 1)][y] = color;
		--w;
	}
}

void draw_rect(int16_t x, int16_t y, int16_t w, int16_t h, uint8_t color)
{
	draw_h_line(x        , y        , w    , color);
	draw_h_line(x        , y + h - 1, w    , color);
	draw_v_line(x        , y + 1    , h - 2, color);
	draw_v_line(x + w - 1, y + 1    , h - 2, color);
}

void fill_rect(int16_t x, int16_t y, int16_t w, int16_t h, uint8_t color)
{
	// Boundary Checks And Corrections
	if(x >= DISPLAY_WIDTH || y >= DISPLAY_HEIGHT) return;
	
	if(y < 0) { h += y;  y = 0; }
	if(y + h > DISPLAY_HEIGHT) h = DISPLAY_HEIGHT - y;
	if(h < 1) return;
	
	if(x < 0) { w += x;  x = 0; }
	if(x + w > DISPLAY_WIDTH) w = DISPLAY_WIDTH - x;
	if(w < 1) return;
	
	while(h)
	{
		int16_t tmp_w = w;
		
		while(tmp_w)
		{
			//vram[(y + h) * DISPLAY_WIDTH + (x + tmp_w)] = color;
			vram[(x + tmp_w - 1)][(y + h - 1)] = color;
			--tmp_w;
		}
		
		--h;
	}
}

void fill_screen(uint8_t color)
{
	memset(vram, color, sizeof(vram));
}

void clear_screen()
{
	memset(vram, 0, sizeof(vram));
}

#if defined(__arm__)

#include "./arm/stm32f411_ili9486l.h"

uint8_t init_display()
{
	tft_start_write();
	init_ili9486l();
	clear_screen();
	tft_end_write();
	return 0;
}

void update_display()
{
	tft_start_write();
	tft_set_write_window(0, 0, 480, 320);
	
	/*for(uint16_t y = 0; y < 320; ++y)
	{
		for(uint16_t x = 0; x < 480; ++x)
		{
			//tft_send_color(rgb332_to_rgb565[vram[(y >> 1) * DISPLAY_WIDTH + (x >> 1)]]);
			tft_send_color(rgb332_to_rgb565[vram[(x >> 1)][(y >> 1)]]);
		}
	}*/

	uint16_t x = 0, y = 0, col = 0;

	while(y < 320)
	{
		x = 0;
		while(x < 240)
		{
			col = rgb332_to_rgb565[(vram[(x)][(y / 2)])];
			//col = ConvertRGB332toRGB565(vram[(x)][(y / 2)]);
			//tft_send_color(col);
			tft_set_data_16(col);
			tft_write_pulse();
			tft_write_pulse();
			x++;
		}
		y++;
	}

	tft_end_write();
}

#elif defined(__WIN32__)

#include <assert.h>

uint8_t init_display()
{
	assert(0 && "WIN32 support for init_display() has not been implemented yet.");
	return (uint8_t)-1;
}

void update_display()
{
	assert(0 && "WIN32 support for update_display() has not been implemented yet.");
}

#else
	#error "Unsupported platform"
#endif // Platform Check
