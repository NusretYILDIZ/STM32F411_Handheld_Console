#include "./graphics_2d.h"

#include "../../display/display_driver.h"

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
	
	/*for(int row = 0; row < h; row++)
	{
		for(int col = 0; col < w; col++)
		{
			uint8_t img_byte = image[row * w / 4 + col / 4];
			uint8_t pixel = 0;
			
			for(int k = 3; k >= 0; k--)
			{
				draw_pixel(x + col, y + row, color[pixel & 0x3]);
				pixel = img_byte >> 2;
				col++;
			}
		}
	}*/
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
	
	/*for(int row = 0; row < h; row++)
	{
		for(int col = 0; col < w; col++)
		{
			uint8_t img_byte = image[row * w / 2 + col / 2];
			uint8_t pixel = 0;
			
			for(int k = 1; k >= 0; k--)
			{
				draw_pixel(x + col, y + row, color[pixel & 0xf]);
				pixel = img_byte >> 4;
				col++;
			}
		}
	}*/
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
	
	/*for(int row = 0; row < h; row++)
	{
		for(int col = 0; col < w; col++)
		{
			uint8_t img_byte = ram[image.image + row * w / 8 + col / 8];
			uint8_t pixel = 0;
			
			for(int k = 7; k >= 0; k--)
			{
				pixel = img_byte >> k;
				draw_pixel(x + col, y + row, ram[image.colors + (pixel & 0x1)]);
				col++;
			}
		}
	}*/
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
	
	/*for(int row = 0; row < h; row++)
	{
		for(int col = 0; col < w; col++)
		{
			uint8_t img_byte = ram[image.image + row * w / 4 + col / 4];
			uint8_t pixel = 0;
			
			for(int k = 3; k >= 0; k--)
			{
				pixel = img_byte >> (k * 2);
				draw_pixel(x + col, y + row, ram[image.colors + (pixel & 0x3)]);
				col++;
			}
		}
	}*/
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
	
	/*for(int row = 0; row < h; row++)
	{
		for(int col = 0; col < w; col++)
		{
			uint8_t img_byte = ram[image.image + row * w / 2 + col / 2];
			uint8_t pixel = 0;
			
			for(int k = 1; k >= 0; k--)
			{
				pixel = img_byte >> (k * 4);
				draw_pixel(x + col, y + row, ram[image.colors + (pixel & 0xf)]);
				col++;
			}
		}
	}*/
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