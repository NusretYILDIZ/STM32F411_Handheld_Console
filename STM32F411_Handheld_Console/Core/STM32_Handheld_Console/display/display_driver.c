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

#include "./display_driver.h"

#include <stdarg.h>
#include <string.h>
#include <stdio.h>

// Taken from: https://blog.frankvh.com/2015/03/29/fast-rgb332-to-rgb565-colorspace-conversion/
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
    0xfec0, 0xfeca, 0xfed5, 0xfedf, 0xffe0, 0xffea, 0xfff5, 0xfff5
    //                                                      ^^^^^^
    // The last value should be 0xffff instead of 0xfff5, but for some reason the breadboard circuit goes nuts.
};

uint8_t vram[DISPLAY_HEIGHT][DISPLAY_WIDTH];
int8_t str_buffer[MAX_STRING_LEN];

GFXfont *gfx_font = &YILDIZsoft_5x7;

int16_t cursor_x = 0;
int16_t cursor_y = 0;

uint8_t text_size_x = 1;
uint8_t text_size_y = 1;

TextArea text_area = { .start_x = 0, .start_y = 0, .end_x = DISPLAY_WIDTH - 1, .end_y = DISPLAY_HEIGHT - 1 };
uint8_t wrap_text = 1;

uint8_t text_fg_color = 0xff;
uint8_t text_bg_color = 0x00;

void draw_raw_pixel(int16_t x, int16_t y, uint8_t color)
{
	vram[y][x] = color;
}

void draw_raw_v_line(int16_t x, int16_t y, int16_t h, uint8_t color)
{
	while(h)
	{
		--h;
		vram[y + h][x] = color;
	}
}

void draw_raw_h_line(int16_t x, int16_t y, int16_t w, uint8_t color)
{
	memset(&vram[y][x], color, w);
}

void draw_raw_rect(int16_t x, int16_t y, int16_t w, int16_t h, uint8_t color)
{
	draw_raw_h_line(x        , y        , w    , color);  // Top horizontal line
	draw_raw_h_line(x        , y + h - 1, w    , color);  // Bottom horizontal line
	draw_raw_v_line(x        , y + 1    , h - 2, color);  // Left vertical line
	draw_raw_v_line(x + w - 1, y + 1    , h - 2, color);  // Right vertical line
}

void fill_raw_rect(int16_t x, int16_t y, int16_t w, int16_t h, uint8_t color)
{
	while(h)
	{
		--h;
		memset(&vram[y + h][x], color, w);
	}
}

void draw_pixel(int16_t x, int16_t y, uint8_t color)
{
	if(x < 0 || x >= DISPLAY_WIDTH || y < 0 || y >= DISPLAY_HEIGHT) return;
	
	vram[y][x] = color;
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
		--h;
		vram[(y + h)][x] = color;
	}
}

void draw_h_line(int16_t x, int16_t y, int16_t w, uint8_t color)
{
	// Boundary Checks And Corrections
	if(x >= DISPLAY_WIDTH || y < 0 || y >= DISPLAY_HEIGHT) return;
	if(x < 0) { w += x;  x = 0; }
	if(x + w > DISPLAY_WIDTH) w = DISPLAY_WIDTH - x;
	if(w < 1) return;
	
	memset(&vram[y][x], color, w);
}

void draw_rect(int16_t x, int16_t y, int16_t w, int16_t h, uint8_t color)
{
	draw_h_line(x        , y        , w    , color);  // Top horizontal line
	draw_h_line(x        , y + h - 1, w    , color);  // Bottom horizontal line
	draw_v_line(x        , y + 1    , h - 2, color);  // Left vertical line
	draw_v_line(x + w - 1, y + 1    , h - 2, color);  // Right vertical line
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
		--h;
		memset(&vram[(y + h)][x], color, w);
	}
}

void fill_display(uint8_t color)
{
	memset(vram, color, sizeof(vram));
}

void clear_display()
{
	memset(vram, 0, sizeof(vram));
}

void draw_bitmap(int16_t x, int16_t y, uint16_t w, uint16_t h, const uint8_t *image)
{
	if(x >= DISPLAY_WIDTH || y >= DISPLAY_HEIGHT || x + w < 0 || y + h < 0) return;
	
	int16_t  tx = x, ty = y;
	uint16_t tw = w, th = h;
	
	int16_t offset_x = 0, offset_y = 0;
	
	if(ty < 0) 
	{ 
		th += ty; 
		offset_y = -ty; 
		ty = 0;
	}
	if(ty + th > DISPLAY_HEIGHT) th = DISPLAY_HEIGHT - ty;
	if(th < 1) return;
	
	if(tx < 0)
	{
		tw += tx;
		offset_x = -tx;
		tx = 0;
	}
	if(tx + tw > DISPLAY_WIDTH) tw = DISPLAY_WIDTH - tx;
	if(tw < 1) return;
	
	while(th)
	{
		--th;
		memcpy(&vram[ty + th][tx], &image[(th + offset_y) * w + offset_x], tw);
	}
}

void set_cursor(int16_t x, int16_t y)
{
	cursor_x = x;
	cursor_y = y;
}

void set_text_size(uint8_t x, uint8_t y)
{
	text_size_x = (x > 0) ? x : 1;
	text_size_y = (y > 0) ? y : 1;
}

void set_text_color(uint8_t fg, uint8_t bg)
{
	text_fg_color = fg;
	text_bg_color = bg;
}

void set_text_wrap(uint8_t wrap)
{
	wrap_text = wrap;
}

void set_text_area(int16_t sx, int16_t sy, int16_t ex, int16_t ey)
{
	text_area.start_x = (sx >= 0) ? sx : 0;
	text_area.start_y = (sy >= 0) ? sy : 0;
	text_area.end_x = (ex < DISPLAY_WIDTH) ? ex : DISPLAY_WIDTH - 1;
	text_area.end_y = (ey < DISPLAY_HEIGHT) ? ey : DISPLAY_HEIGHT - 1;
}

void set_font_helper(const GFXfont *new_font)
{
	gfx_font = (GFXfont *) new_font;
}

void set_font(const uint8_t font)
{
	switch(font)
	{
	case 1:
		set_font_helper(&Minecraft_5x7);
		break;
	
	default:
		set_font_helper(&YILDIZsoft_5x7);
		break;
	}
}

GFXfont *get_current_font(void)
{
	return gfx_font;
}

uint8_t get_font_height(void)
{
	return gfx_font->yAdvance * text_size_y;
}

uint8_t get_char_width(unsigned char c)
{
	return (gfx_font->glyph + c - gfx_font->first)->xAdvance * text_size_x;
}

void char_bounds(unsigned char c, int16_t *x, int16_t *y, int16_t *min_x, int16_t *min_y, int16_t *max_x, int16_t *max_y)
{
	if(c == '\n')
	{
		*x = text_area.start_x;
		*y += text_size_y * gfx_font->yAdvance;
	}
	else if(c != '\r')
	{
		if((c >= gfx_font->first) && (c <= gfx_font->last))
		{
			c -= gfx_font->first;
			GFXglyph *glyph  = gfx_font->glyph + c;
			
			if(wrap_text && ((*x + ((glyph->xOffset + glyph->width) * text_size_x)) > text_area.end_x))
			{
				*x  = text_area.start_x;
				*y += text_size_y * gfx_font->yAdvance;
			}
			
			int16_t x1 = *x, // + glyph->xOffset * text_size_x    ,
					y1 = *y, // + glyph->yOffset * text_size_y    ,
					x2 = x1 + glyph->width * text_size_x - 1,
					y2 = y1 + gfx_font->yAdvance * text_size_y - 1;
					//y2 = y1 + glyph->height  * text_size_y - 1;
			
			if(x1 < *min_x) *min_x = x1;
			if(y1 < *min_y) *min_y = y1;
			if(x2 > *max_x) *max_x = x2;
			if(y2 > *max_y) *max_y = y2;
			
			*x += glyph->xAdvance * text_size_x;
		}
	}
}

void text_bounds(const char *str, int16_t x, int16_t y, int16_t *x1, int16_t *y1, uint16_t *w, uint16_t *h)
{
	unsigned char c;
	int16_t min_x = 0x7FFF, min_y = 0x7FFF, max_x = -1, max_y = -1;
	
	*x1 = x;
	*y1 = y;
	*w = *h = 0;
	
	while((c = *str++))
	{
		char_bounds(c, &x, &y, &min_x, &min_y, &max_x, &max_y);
	}
	
	if(max_x >= min_x)
	{
		*x1 = min_x;
		*w = max_x - min_x + 1;
	}
	if(max_y >= min_y)
	{
		*y1 = min_y;
		*h = max_y - min_y + 1;
	}
}

void display_char(int16_t x, int16_t y, uint8_t c, uint8_t text_color, uint8_t bg_color, uint8_t size_x, uint8_t size_y)
{	
	c -= gfx_font->first;
	GFXglyph *glyph = gfx_font->glyph + c;
	uint8_t *bitmap = gfx_font->bitmap;
	
	uint16_t glyph_bo = glyph->bitmapOffset;
	uint8_t glyph_w = glyph->width;
	uint8_t glyph_h = glyph->height;
	int8_t glyph_xo = glyph->xOffset;
	int8_t glyph_yo = glyph->yOffset;
	uint8_t bits = 0, bit = 0;
	int xx, yy;
	
	for(yy = 0; yy < glyph_h; ++yy)
	{
		if((y + (yy + glyph_yo) * size_y < text_area.start_y) || (y + (yy + glyph_yo) * size_y > text_area.end_y)) continue;
		
		for(xx = 0; xx < glyph_w; ++xx)
		{
			if(!(bit++ & 7))
				bits = bitmap[glyph_bo++];
			
			if(x + (xx + glyph_xo) * size_x < text_area.start_x || x + (xx + glyph_xo) * size_x > text_area.end_x)
			{
				bits <<= 1;
				continue;
			}

			if(bits & 0x80)
			{
				if(size_x == 1 && size_y == 1)
					draw_raw_pixel(x + glyph_xo + xx, y + glyph_yo + yy, text_color);
				else
					fill_raw_rect(x + (glyph_xo + xx) * size_x, y + (glyph_yo + yy) * size_y, size_x, size_y, text_color);
			}
			
			bits <<= 1;
		}
	}
}

void print_chr(uint8_t c)
{
	if(c == '\n')
	{
		cursor_x = text_area.start_x;
		cursor_y += text_size_y * gfx_font->yAdvance;
	}
	else if(c != '\r')
	{
		uint8_t first = gfx_font->first;
		
		if((c >= first) && (c <= gfx_font->last))
		{
			GFXglyph *glyph = gfx_font->glyph + c - first;
			uint8_t w = glyph->width;
			uint8_t h = glyph->height;
			
			if(w > 0 && h > 0)
			{
				int16_t xo = glyph->xOffset;
				
				if(wrap_text && (cursor_x + text_size_x * (xo + w)) > text_area.end_x)
				{
					cursor_x = text_area.start_x;
					cursor_y += text_size_y * gfx_font->yAdvance;
				}
				display_char(cursor_x, cursor_y, c, text_fg_color, text_bg_color, text_size_x, text_size_y);
			}
			
			cursor_x += text_size_x * glyph->xAdvance;
		}
	}
}

void print_str(const char* str)
{
	size_t len = strlen(str);
	
	while(len--)
	{
		if(*str)
		{
			print_chr(*str);
			++str;
		}
		else return;
	}
}

void print_int(long num)
{
	char buffer[8 * sizeof(long) + 1] = { '\0' };
	char *str = &buffer[sizeof(buffer) - 1];
	
	*str = '\0';
	
	if(num < 0)
	{
		print_chr('-');
		num = -num;
	}
	
	do
	{
		char c = num % 10;
		num /= 10;
		
		*--str = c + '0';
	} while(num);
	
	print_str(str);
}

void printf_str(const char *text, ...)
{
	memset(str_buffer, '\0', sizeof(str_buffer));
	va_list args;
	
	va_start(args, text);
	vsnprintf(str_buffer, sizeof(str_buffer), text, args);
	va_end(args);
	
	print_str(str_buffer);
}


#if defined(__arm__)

#include "./arm/stm32f411_ili9486l.h"

uint8_t init_display()
{
	memset(vram, 0, sizeof(vram));
	memset(str_buffer, '\0', sizeof(str_buffer));
	
	tft_start_write();
	init_ili9486l();
	clear_display();
	tft_end_write();
	//set_font(1);
	set_text_area(0, 0, DISPLAY_WIDTH - 1, DISPLAY_HEIGHT - 1);
	return 0;
}

void update_display()
{
	tft_start_write();
	tft_set_write_window(0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);
	
	for(int y = 0; y < SCREEN_HEIGHT; ++y)
	{
		for(int x = 0; x < SCREEN_WIDTH / 2; ++x)
		{
			tft_set_data_16(rgb332_to_rgb565[(vram[(y / 2)][(x)])]);
			tft_write_pulse();
			tft_write_pulse();
		}
	}

	tft_end_write();
}

#elif defined(__WIN32__)

#include <assert.h>
#include <stdlib.h>
#include "./win32/win32_sdl2_include.h"

SDL_Window   *sdl_display_window   = 0;
SDL_Renderer *sdl_display_renderer = 0;
SDL_Texture  *sdl_display_texture  = 0;
SDL_Surface  *sdl_display_surface  = 0;

uint8_t init_display()
{
	memset(vram, 0, sizeof(vram));
	memset(str_buffer, '\0', sizeof(str_buffer));
	
	sdl_display_window = SDL_CreateWindow("STM32F411 Handheld Console Emulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 240 * 4, 160 * 4, SDL_WINDOW_MAXIMIZED | SDL_WINDOW_RESIZABLE | SDL_WINDOW_INPUT_FOCUS);
	if(!sdl_display_window)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "STM32F411 Handheld Console Emulator", "SDL_CreateWindow failed in init_display() function.", 0);
		exit(1);
	}
	
	sdl_display_renderer = SDL_CreateRenderer(sdl_display_window, -1, SDL_RENDERER_SOFTWARE | SDL_RENDERER_PRESENTVSYNC);
	if(!sdl_display_renderer)
	{
		SDL_DestroyWindow(sdl_display_window);
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "STM32F411 Handheld Console Emulator", "SDL_CreateRenderer failed in init_display() function.", 0);
		exit(1);
	}
	
	clear_display();
	//set_font(1);
	set_text_area(0, 0, DISPLAY_WIDTH - 1, DISPLAY_HEIGHT - 1);
	
	return 0;
}

void update_display()
{
	sdl_display_surface = SDL_CreateRGBSurfaceFrom(vram, 240, 160, 8, 240, 0b11100000, 0b00011100, 0b00000011, 0);
	
	if(!sdl_display_surface)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "STM32F411 Handheld Console Emulator", "SDL_CreateRGBSurfaceFrom failed in update_display() function.", 0);
		exit(1);
	}
	
	sdl_display_texture = SDL_CreateTextureFromSurface(sdl_display_renderer, sdl_display_surface);
	
	int window_w, window_h;
	SDL_GetWindowSize(sdl_display_window, &window_w, &window_h);
	
	SDL_Rect sdl_display_rect = { 0 };
	
	if((window_w * 2) > (3 * window_h))  // Window is wider than rendered display
	{
		sdl_display_rect.w = window_h * 3 / 2;
		sdl_display_rect.h = window_h;
		sdl_display_rect.x = (window_w - sdl_display_rect.w) / 2;
		sdl_display_rect.y = 0;
	}
	else if((window_w * 2) < (3 * window_h))  // Window is narrower than rendered display
	{
		sdl_display_rect.w = window_w;
		sdl_display_rect.h = window_w * 2 / 3;
		sdl_display_rect.x = 0;
		sdl_display_rect.y = (window_h - sdl_display_rect.h) / 2;
	}
	else  // Window's aspect ratio is same as rendered display
	{
		sdl_display_rect.w = window_w;
		sdl_display_rect.h = window_h;
		sdl_display_rect.x = 0;
		sdl_display_rect.y = 0;
	}
	
	SDL_RenderCopy(sdl_display_renderer, sdl_display_texture, 0, &sdl_display_rect);
	SDL_RenderPresent(sdl_display_renderer);
	
	SDL_DestroyTexture(sdl_display_texture);
	SDL_FreeSurface(sdl_display_surface);
}

#elif defined(__ANDROID__)
	#error "Android version of display driver is not implemented yet."
#else
	#error "Unsupported platform"
#endif // Platform Check
