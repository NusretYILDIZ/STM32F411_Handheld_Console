#ifndef __system_main_h
#define __system_main_h

#include "./popup.h"
#include "./menu.h"
#include "./timer.h"
#include "../display/display_driver.h"
#include "../input/input_driver.h"
#include "../game_engine/game_engine.h"

uint8_t system_main(void);
void system_list_games(void);
void system_options(void);
void system_about(void);

#endif //__system_main_h