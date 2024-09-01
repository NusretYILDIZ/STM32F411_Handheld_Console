#ifndef __graphics_2d_h
#define __graphics_2d_h

#include "../script/script_engine.h"

typedef enum
{
	IMG_NO_PALETTE,
	IMG_2_COLORS,
	IMG_4_COLORS,
	IMG_16_COLORS,
} IMG_PALETTE;

typedef struct
{
	uint8_t palette;
	RAM_PTR colors;
	RAM_PTR image;
} IMAGE;

void draw_image(int16_t x, int16_t y, uint16_t w, uint16_t h, IMAGE image);
void draw_image_from_flash(int16_t x, int16_t y, uint16_t w, uint16_t h, IMAGE image);

#endif //__graphics_2d_h