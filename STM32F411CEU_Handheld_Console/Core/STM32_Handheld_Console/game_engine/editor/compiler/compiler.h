#ifndef __compiler_h
#define __compiler_h

#include "../../game_engine.h"
#include "../../../system/popup.h"

uint8_t parentheses_balanced(char *src);
uint8_t compile(char *src, char *bin);

#endif //__compiler_h