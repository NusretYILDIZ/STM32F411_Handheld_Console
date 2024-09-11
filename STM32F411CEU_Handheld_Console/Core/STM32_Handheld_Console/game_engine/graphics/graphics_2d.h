#ifndef __graphics_2d_h
#define __graphics_2d_h

#include <stdarg.h>

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

#define TEXT_H_ALIGN_LEFT    (0 << 0)
#define TEXT_H_ALIGN_CENTER  (1 << 0)
#define TEXT_H_ALIGN_RIGHT   (2 << 0)

#define TEXT_V_ALIGN_TOP     (0 << 2)
#define TEXT_V_ALIGN_CENTER  (1 << 2)
#define TEXT_V_ALIGN_BOTTOM  (2 << 2)

#define TEXT_H_ALIGN_MASK  (3 << 0)
#define TEXT_V_ALIGN_MASK  (3 << 2)

#define get_text_h_align(x)  (x & TEXT_H_ALIGN_MASK)
#define get_text_v_align(x)  (x & TEXT_V_ALIGN_MASK)

void draw_image(int16_t x, int16_t y, uint16_t w, uint16_t h, IMAGE image);
void draw_image_from_flash(int16_t x, int16_t y, uint16_t w, uint16_t h, IMAGE image);
void draw_text(int16_t x, int16_t y, uint8_t text_flags, char *text);
void draw_formatted_text(int16_t x, int16_t y, uint8_t text_flags, char *text, ...);
void draw_char(int16_t x, int16_t y, uint8_t text_flags, char c);

#endif //__graphics_2d_h