#include "./graphics_2d.h"

#include "../../display/display_driver.h"

#include <stdio.h>
#include <string.h>

void draw_image_from_flash_helper_2_colors(int16_t x, int16_t y, uint16_t w, uint16_t h, uint8_t *color, uint8_t *image)
{
	uint8_t pixel = 0;
	uint16_t bits = 0;
	uint16_t offset = 0;
	
	for(int row = 0; row < h; row++)
	{
		for(int col = 0; col < w; col++)
		{
			if(!(bits++ & 7)) pixel = image[offset++];
			
			draw_pixel(x + col, y + row, color[(pixel >> 7) & 0x1]);
			pixel <<= 1;
		}
		if(w & 7) bits = 0;
	}
}

void draw_image_from_flash_helper_4_colors(int16_t x, int16_t y, uint16_t w, uint16_t h, uint8_t *color, uint8_t *image)
{
	uint8_t pixel = 0;
	uint16_t bits = 0;
	uint16_t offset = 0;
	
	for(int row = 0; row < h; row++)
	{
		for(int col = 0; col < w; col++)
		{
			if(!(bits++ & 3)) pixel = image[offset++];
			
			draw_pixel(x + col, y + row, color[(pixel >> 6) & 0x3]);
			pixel <<= 2;
		}
		if(w & 3) bits = 0;
	}
}

void draw_image_from_flash_helper_16_colors(int16_t x, int16_t y, uint16_t w, uint16_t h, uint8_t *color, uint8_t *image)
{
	uint8_t pixel = 0;
	uint16_t bits = 0;
	uint16_t offset = 0;
	
	for(int row = 0; row < h; row++)
	{
		for(int col = 0; col < w; col++)
		{
			if(!(bits++ & 1)) pixel = image[offset++];
			
			draw_pixel(x + col, y + row, color[(pixel >> 4) & 0xf]);
			pixel <<= 4;
		}
		if(w & 1) bits = 0;
	}
}

void draw_image_helper_2_colors(int16_t x, int16_t y, uint16_t w, uint16_t h, IMAGE image)
{
	uint8_t pixel = 0;
	uint16_t bits = 0;
	uint16_t offset = 0;
	
	for(int row = 0; row < h; row++)
	{
		for(int col = 0; col < w; col++)
		{
			if(!(bits++ & 7)) pixel = ram[image.image + offset++];
			
			draw_pixel(x + col, y + row, ram[image.colors + (pixel >> 7) & 0x1]);
			pixel <<= 1;
		}
		if(w & 7) bits = 0;
	}
}

void draw_image_helper_4_colors(int16_t x, int16_t y, uint16_t w, uint16_t h, IMAGE image)
{
	uint8_t pixel = 0;
	uint16_t bits = 0;
	uint16_t offset = 0;
	
	for(int row = 0; row < h; row++)
	{
		for(int col = 0; col < w; col++)
		{
			if(!(bits++ & 3)) pixel = ram[image.image + offset++];
			
			draw_pixel(x + col, y + row, ram[image.colors + (pixel >> 6) & 0x3]);
			pixel <<= 2;
		}
		if(w & 3) bits = 0;
	}
}

void draw_image_helper_16_colors(int16_t x, int16_t y, uint16_t w, uint16_t h, IMAGE image)
{
	uint8_t pixel = 0;
	uint16_t bits = 0;
	uint16_t offset = 0;
	
	for(int row = 0; row < h; row++)
	{
		for(int col = 0; col < w; col++)
		{
			if(!(bits++ & 1)) pixel = ram[image.image + offset++];
			
			draw_pixel(x + col, y + row, ram[image.colors + (pixel >> 4) & 0xf]);
			pixel <<= 4;
		}
		if(w & 1) bits = 0;
	}
}

void draw_image(int16_t x, int16_t y, uint16_t w, uint16_t h, IMAGE image)
{
	switch(image.palette)
	{
	case IMG_NO_PALETTE:
		draw_bitmap(x, y, w, h, &ram[image.image]);
		break;
	
	case IMG_2_COLORS:
		draw_image_helper_2_colors(x, y, w, h, image);
		break;
	
	case IMG_4_COLORS:
		draw_image_helper_4_colors(x, y, w, h, image);
		break;
	
	case IMG_16_COLORS:
		draw_image_helper_16_colors(x, y, w, h, image);
		break;
	}
}

void draw_image_from_flash(int16_t x, int16_t y, uint16_t w, uint16_t h, IMAGE image)
{
	switch(image.palette)
	{
	case IMG_NO_PALETTE:
		draw_bitmap(x, y, w, h, (uint8_t *)(image.image));
		break;
	
	case IMG_2_COLORS:
		draw_image_from_flash_helper_2_colors(x, y, w, h, (uint8_t *)(image.colors), (uint8_t *)(image.image));
		break;
	
	case IMG_4_COLORS:
		draw_image_from_flash_helper_4_colors(x, y, w, h, (uint8_t *)(image.colors), (uint8_t *)(image.image));
		break;
	
	case IMG_16_COLORS:
		draw_image_from_flash_helper_16_colors(x, y, w, h, (uint8_t *)(image.colors), (uint8_t *)(image.image));
		break;
	}
}

void draw_text(int16_t x, int16_t y, uint8_t text_flags, char *text)
{
	uint8_t text_h_align = get_text_h_align(text_flags);
	uint8_t text_v_align = get_text_v_align(text_flags);
	
	int16_t text_x, text_y;
	uint16_t text_w, text_h;
	
	text_bounds(text, 0, 0, &text_x, &text_y, &text_w, &text_h);
	
	     if(text_h_align == TEXT_H_ALIGN_CENTER) text_x = x - text_w / 2;
	else if(text_h_align == TEXT_H_ALIGN_RIGHT ) text_x = x - text_w;
	else text_x = x;
	
	     if(text_v_align == TEXT_V_ALIGN_TOP   ) text_y = y + text_h;
	else if(text_v_align == TEXT_V_ALIGN_CENTER) text_y = y + text_h / 2;
	else text_y = y;
	
	set_cursor(text_x, text_y);
	print_str(text);
}

void draw_formatted_text(int16_t x, int16_t y, uint8_t text_flags, char *text, ...)
{
	uint8_t text_h_align = get_text_h_align(text_flags);
	uint8_t text_v_align = get_text_v_align(text_flags);
	
	int16_t text_x, text_y;
	uint16_t text_w, text_h;
	
	memset(str_buffer, '\0', sizeof(str_buffer));
	va_list args;
	
	va_start(args, text);
	vsnprintf(str_buffer, sizeof(str_buffer), text, args);
	va_end(args);
	
	text_bounds(str_buffer, 0, 0, &text_x, &text_y, &text_w, &text_h);
	
	     if(text_h_align == TEXT_H_ALIGN_CENTER) text_x = x - text_w / 2;
	else if(text_h_align == TEXT_H_ALIGN_RIGHT ) text_x = x - text_w;
	else text_x = x;
	
	     if(text_v_align == TEXT_V_ALIGN_TOP   ) text_y = y + text_h;
	else if(text_v_align == TEXT_V_ALIGN_CENTER) text_y = y + text_h / 2;
	else text_y = y;
	
	set_cursor(text_x, text_y);
	print_str(str_buffer);
}

void draw_char(int16_t x, int16_t y, uint8_t text_flags, char c)
{
	uint8_t text_h_align = get_text_h_align(text_flags);
	uint8_t text_v_align = get_text_v_align(text_flags);
	
	int16_t text_x, text_y;
	uint16_t text_w, text_h;
	
	char text[2] = { '\0' };
	text[0] = c;
	
	text_bounds(text, 0, 0, &text_x, &text_y, &text_w, &text_h);
	
	     if(text_h_align == TEXT_H_ALIGN_CENTER) text_x = x - text_w / 2;
	else if(text_h_align == TEXT_H_ALIGN_RIGHT ) text_x = x - text_w;
	else text_x = x;
	
	     if(text_v_align == TEXT_V_ALIGN_TOP   ) text_y = y + get_font_height();
	else if(text_v_align == TEXT_V_ALIGN_CENTER) text_y = y + get_font_height() / 2;
	else text_y = y;
	
	set_cursor(text_x, text_y);
	print_str(text);
}