#ifndef __script_engine_h
#define __script_engine_h

#include <stdint.h>
#include "../../display/display_driver.h"

#define RAM_SIZE        (1024 * 80) // 80 KB
#define STACK_SIZE      (256)
#define RPN_STACK_SIZE  (32)

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;

#if (RAM_SIZE > 65536)
	typedef uint32_t RAM_PTR;
#else
	typedef uint16_t RAM_PTR;
#endif

#if (STACK_SIZE > 256)
	typedef uint16_t STACK_PTR;
#else
	typedef uint8_t STACK_PTR;
#endif

extern uint8_t ram[RAM_SIZE];
//extern uint32_t stack[STACK_SIZE];

extern RAM_PTR prg_counter;
extern STACK_PTR stack_ptr;

extern uint8_t status_flag;

typedef union
{
	float flt;
	int32_t int32;
	int16_t int16;
	int8_t int8;
	uint32_t uint32;
	uint16_t uint16;
	uint8_t uint8;
	RAM_PTR ram_ptr;
	STACK_PTR stack_ptr;
} MEM_BUF;

#define PANIC_CODES(X)  X(NONE) \
                        X(UNKNOWN_DATA_TYPE) \
                        X(UNKNOWN_ADDR_MODE) \
                        X(INVALID_INSTRUCTION) \
                        X(DATA_TYPE_DISCREPANCY) \
                        X(STACK_OVERFLOW) \
                        X(STACK_UNDERFLOW) \
                        X(RPN_SOLVER_FAILED) \
                        X(RPN_SOLVER_TOO_MANY_RESULTS) \
                        X(RPN_SOLVER_UNKNOWN_TYPE) \
                        X(RPN_SOLVER_UNKNOWN_ADDR_MODE) \
                        X(RPN_SOLVER_UNKNOWN_OPERATOR) \
                        X(RPN_SOLVER_DIVIDE_BY_ZERO) \
                        X(RPN_STACK_OVERFLOW) \
                        X(RPN_STACK_UNDERFLOW)

#define PANIC_ENUMS(CODE) PANIC_##CODE,
#define PANIC_NAMES(CODE) #CODE,

typedef enum
{
	PANIC_CODES(PANIC_ENUMS)
} PANIC_CODE;

extern PANIC_CODE panic_code;

#define KERNEL_PANIC(code)  do { \
                                status_flag |= KERNEL_PANIC_FLAG; \
                                panic_code = code; \
                            } while(0)

#define CLEAR_KERNEL_PANIC()  do { \
                                  status_flag &= ~KERNEL_PANIC_FLAG; \
                                  panic_code = PANIC_NONE; \
                              } while(0)

#define CLEAR_END_OF_LOOP()  status_flag &= ~END_OF_LOOP_FLAG


typedef enum
{
	RPN_TYPE_NONE,
	RPN_TYPE_TERMINATE,
	RPN_TYPE_ERROR,
	RPN_TYPE_NUMERAL,

	RPN_TYPE_ADD,             // +
	RPN_TYPE_SUB,             // -
	RPN_TYPE_MUL,             // *
	RPN_TYPE_DIV,             // /
	RPN_TYPE_MOD,             // %
	RPN_TYPE_MINUS,           // -1 (single operand)

	RPN_TYPE_BITWISE_AND,     // &
	RPN_TYPE_BITWISE_OR,      // |
	RPN_TYPE_BITWISE_XOR,     // ^
	RPN_TYPE_BITWISE_NOT,     // ~ (single operand)
	RPN_TYPE_BITSHIFT_LEFT,   // <<
	RPN_TYPE_BITSHIFT_RIGHT,  // >>

	RPN_TYPE_EQUAL,           // ==
	RPN_TYPE_NOT_EQUAL,       // !=
	RPN_TYPE_LESS,            // <
	RPN_TYPE_GREATER,         // >
	RPN_TYPE_LESS_EQUAL,      // <=
	RPN_TYPE_GREATER_EQUAL,   // >=

	RPN_TYPE_LOGICAL_AND,     // &&
	RPN_TYPE_LOGICAL_OR,      // ||
	RPN_TYPE_LOGICAL_NOT,     // ! (single operand)
} RPN_TYPE;

typedef struct
{
	uint8_t type;
	uint8_t attr;
	MEM_BUF value;
} RPN_DATA;


typedef enum
{
	RPNS_TYPE_ERROR,
	RPNS_TYPE_INT64,
	RPNS_TYPE_FLOAT,
} RPN_STACK_TYPE;

typedef struct
{
	uint8_t type;
	union {
		int64_t int64;
		float float32;
	} value;
} RPN_STACK_DATA;

extern RPN_STACK_DATA rpn_stack[RPN_STACK_SIZE];
extern uint8_t rpn_stack_ptr;

void vm_init(void);
void vm_execute(void);
void vm_run(void);
void vm_push(uint32_t data);
uint32_t vm_pop(void);

#endif //__script_engine_h