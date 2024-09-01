#ifndef __input_driver_h
#define __input_driver_h

#include <stdint.h>

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
#define GAMEPAD_L1          0x1000
#define GAMEPAD_R1          0x2000
#define GAMEPAD_L2          0x4000
#define GAMEPAD_R2          0x8000

#define AXIS_LEFT_X         0
#define AXIS_LEFT_Y         1
#define AXIS_RIGHT_X        2
#define AXIS_RIGHT_Y        3

extern const uint16_t keys[15];

//#define JOYSTICK_LEFT     0
//#define JOYSTICK_RIGHT    1

extern uint16_t current_keys;
extern uint16_t previous_keys;
extern int8_t axises[4];

extern uint16_t key_held_frames[15];
extern uint16_t first_hold_time;
extern uint16_t hold_interval;

/*typedef struct
{
	float x;
	float y;
} Joystick;

extern Joystick joysticks[2];*/

void init_inputs(void);
void update_inputs(void);
void update_status(void);

uint8_t get_key(uint16_t key_code);
uint8_t get_key_down(uint16_t key_code);
uint8_t get_key_up(uint16_t key_code);
uint8_t get_key_held(uint16_t key_code);
uint8_t get_key_held_for_time(uint16_t key_code);

//float get_joystick_x(uint8_t joystick);
//float get_joystick_y(uint8_t joystick);

#endif //__input_driver_h
