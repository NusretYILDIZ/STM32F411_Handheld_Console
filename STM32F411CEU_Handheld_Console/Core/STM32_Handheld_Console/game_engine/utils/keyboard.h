#ifndef __keyboard_h
#define __keyboard_h

#include "../script/script_engine.h"

#define KB_UPPERCASE  (1 << 0)
#define KB_SYMBOLS    (1 << 1)
#define KB_SYMBOLS2   (1 << 2)

#define MAX_INPUT_LEN  (127)

extern char text_buffer[MAX_INPUT_LEN + 1];

extern uint8_t selected_row;
extern uint8_t selected_col;
extern uint8_t kb_flags;

void show_input_screen(RAM_PTR dest, uint8_t max_len, char *title);

#endif //__keyboard_h