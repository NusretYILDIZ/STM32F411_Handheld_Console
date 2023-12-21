#ifndef __display_driver_h
#define __display_driver_h

#include <stdint.h>

#define DISPLAY_WIDTH  240
#define DISPLAY_HEIGHT 160

#define rgb888_to_rgb332(r, g, b)    ((((r) >> 5) << 5) | (((g) >> 5) << 2) | ((b) >> 6))

extern uint8_t vram[DISPLAY_WIDTH][DISPLAY_HEIGHT];
extern const uint16_t rgb332_to_rgb565[256];

uint8_t init_display(void);
void update_display(void);

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
void set_font(const void *font);
void draw_char(const char c);
void printf_display(const char *text, ...);

#endif // __display_driver_h