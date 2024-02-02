#ifndef __display_driver_h
#define __display_driver_h

#include <stdint.h>
#include "./gfxfont.h"

#define DISPLAY_WIDTH  240
#define DISPLAY_HEIGHT 160

#define rgb888_to_rgb332(r, g, b)    ((((r) >> 5) << 5) | (((g) >> 5) << 2) | ((b) >> 6))

extern const uint16_t rgb332_to_rgb565[256];
extern uint8_t vram[DISPLAY_WIDTH][DISPLAY_HEIGHT];
extern GFXfont *gfx_font;

extern int16_t cursor_x;
extern int16_t cursor_y;

extern uint8_t text_size_x;
extern uint8_t text_size_y;

typedef struct
{
	uint8_t start_x;
	uint8_t start_y;
	uint8_t end_x;
	uint8_t end_y;
} TextArea;

extern TextArea text_area;
extern uint8_t wrap_text;

extern uint8_t text_bg_color;
extern uint8_t text_fg_color;

uint8_t init_display(void);
void update_display(void);

void draw_raw_pixel(int16_t _x, int16_t _y, uint8_t color);
void draw_raw_v_line(int16_t x, int16_t y, int16_t h, uint8_t color);
void draw_raw_h_line(int16_t x, int16_t y, int16_t w, uint8_t color);
void draw_raw_rect(int16_t x, int16_t y, int16_t w, int16_t h, uint8_t color);
void fill_raw_rect(int16_t x, int16_t y, int16_t w, int16_t h, uint8_t color);
void draw_pixel(int16_t _x, int16_t _y, uint8_t color);
void draw_v_line(int16_t x, int16_t y, int16_t h, uint8_t color);
void draw_h_line(int16_t x, int16_t y, int16_t w, uint8_t color);
void draw_rect(int16_t x, int16_t y, int16_t w, int16_t h, uint8_t color);
void fill_rect(int16_t x, int16_t y, int16_t w, int16_t h, uint8_t color);
void fill_screen(uint8_t color);
void clear_screen(void);
void draw_image_from_file(int16_t x, int16_t y, const char *file_path, uint8_t tint);
void draw_image_from_ram(int16_t x, int16_t y, const void *image, uint8_t tint);

void set_cursor(int16_t x, int16_t y);
void set_text_size(uint8_t x, uint8_t y);
void set_text_color(uint8_t fg, uint8_t bg);
void set_text_wrap(uint8_t wrap);
void set_text_area(uint8_t sx, uint8_t sy, uint8_t ex, uint8_t ey);
void set_font(const GFXfont *font);
void char_bounds(unsigned char c, int16_t *x, int16_t *y, int16_t *min_x, int16_t *min_y, int16_t *max_x, int16_t *max_y);
void text_bounds(const char *str, int16_t x, int16_t y, int16_t *x1, int16_t *y1, uint16_t *w, uint16_t *h);
void draw_char(int16_t x, int16_t y, uint8_t c, uint8_t text_color, uint8_t bg_color, uint8_t size_x, uint8_t size_y);
void print_chr(uint8_t c);
void print_str(const char* str);
void print_int(long num);
void printf_display(const char *text, ...);

#endif // __display_driver_h
