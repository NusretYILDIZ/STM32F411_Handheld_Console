#ifndef __input_driver_h
#define __input_driver_h

#define GAMEPAD_DPAD_UP     0x0001
#define GAMEPAD_DPAD_RIGHT  0x0002
#define GAMEPAD_DPAD_DOWN   0x0004
#define GAMEPAD_DPAD_LEFT   0x0008
#define GAMEPAD_X           0x0010
#define GAMEPAD_Y           0x0020
#define GAMEPAD_A           0x0040
#define GAMEPAD_B           0x0080
#define GAMEPAD_SELECT      0x0100
#define GAMEPAD_HOME        0x0200
#define GAMEPAD_START       0x0400
#define GAMEPAD_L           0x1000
#define GAMEPAD_R           0x2000

#define JOYSTICK_LEFT     0
#define JOYSTICK_RIGHT    1

#include <stdint.h>

extern uint16_t current_keys;
extern uint16_t previous_keys;

typedef struct
{
	float x;
	float y;
} Joystick;

extern Joystick joysticks[2];

void update_inputs(void);

uint8_t get_key(uint16_t key_code);
uint8_t get_key_down(uint16_t key_code);
uint8_t get_key_up(uint16_t key_code);
uint8_t get_key_held(uint16_t key_code);

float get_joystick_x(uint8_t joystick);
float get_joystick_y(uint8_t joystick);

#endif //__input_driver_h