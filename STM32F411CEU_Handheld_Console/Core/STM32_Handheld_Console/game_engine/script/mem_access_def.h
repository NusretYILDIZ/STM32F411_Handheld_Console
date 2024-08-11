#ifndef __mem_access_def_h
#define __mem_access_def_h

#include <stdint.h>
#include "./script_engine.h"

#define ram_ptr_float(addr)   (*(float    *)(&ram[(addr)]))
#define ram_ptr_int8(addr)    (*(int8_t   *)(&ram[(addr)]))
#define ram_ptr_int16(addr)   (*(int16_t  *)(&ram[(addr)]))
#define ram_ptr_int32(addr)   (*(int32_t  *)(&ram[(addr)]))
#define ram_ptr_uint8(addr)   (               ram[(addr)] )
#define ram_ptr_uint16(addr)  (*(uint16_t *)(&ram[(addr)]))
#define ram_ptr_uint32(addr)  (*(uint32_t *)(&ram[(addr)]))
#define ram_ptr_addr(addr)    (*(RAM_PTR    *)(&ram[(addr)]))

#define read_attrib(addr_mode, data_type, oper_type)    do { \
                                                            addr_mode = ram[prg_counter] & ADDR_MASK; \
                                                            data_type = ram[prg_counter] & TYPE_MASK; \
                                                            oper_type = ram[prg_counter] & OPER_MASK; \
                                                            ++prg_counter; \
                                                        } while(0)

//#define read_addr(dest_addr, addr_mode)   do { \
                                              dest_addr = ram_ptr_addr(prg_counter); \
                                              if(addr_mode == ADDR_PTR) dest_addr = ram_ptr_addr(dest_addr); \
                                              prg_counter += sizeof(RAM_PTR); \
                                          } while(0)

#define set_read_addr(addr, addr_mode, data_type)    do { \
                                                         if(addr_mode == ADDR_IMM) { \
                                                             addr = prg_counter; \
                                                             prg_counter += ((data_type == TYPE_FLOAT) || (data_type == TYPE_INT32) || (data_type == TYPE_UINT32)) ? sizeof(uint32_t) \
                                                             : ((data_type == TYPE_INT16) || (data_type == TYPE_UINT16)) ? sizeof(uint16_t) \
                                                             : sizeof(uint8_t); \
                                                         } \
														 else { \
														     read_addr(addr, addr_mode); \
														 } \
                                                     } while(0)

#define read_float(buf, addr)		do { \
										buf = ram_ptr_float(addr); \
									} while(0)
                            
#define read_int32(buf, addr)		do { \
										buf = ram_ptr_int32(addr); \
									} while(0)
                            
#define read_int16(buf, addr)		do { \
										buf = ram_ptr_int16(addr); \
									} while(0)
                            
#define read_int8(buf, addr)		do { \
										buf = ram_ptr_int8(addr); \
									} while(0)

#define read_uint32(buf, addr)		do { \
										buf = ram_ptr_uint32(addr); \
									} while(0)

#define read_uint16(buf, addr)		do { \
										buf = ram_ptr_uint16(addr); \
									} while(0)

#define read_uint8(buf, addr)		do { \
										buf = ram_ptr_uint8(addr); \
									} while(0)

/*#define read_float(buf)     do { \
                                buf = *(float *) (&ram[prg_counter]); \
                                prg_counter += sizeof(float); \
                            } while(0)
                            
#define read_int32(buf)     do { \
                                buf = *(int32_t *) (&ram[prg_counter]); \
                                prg_counter += sizeof(int32_t); \
                            } while(0)
                            
#define read_int16(buf)     do { \
                                buf = *(int16_t *) (&ram[prg_counter]); \
                                prg_counter += sizeof(int16_t); \
                            } while(0)
                            
#define read_int8(buf)      do { \
                                buf = *(int8_t *) (&ram[prg_counter]); \
                                ++prg_counter; \
                            } while(0)

#define read_uint32(buf)    do { \
                                buf = *(uint32_t *) (&ram[prg_counter]); \
                                prg_counter += sizeof(uint32_t); \
                            } while(0)

#define read_uint16(buf)    do { \
                                buf = *(uint16_t *) (&ram[prg_counter]); \
                                prg_counter += sizeof(uint16_t); \
                            } while(0)

#define read_uint8(buf)     do { \
                                buf = ram[prg_counter]; \
                                ++prg_counter; \
                            } while(0)*/

#define write_float(dat, addr)		do { \
										ram_ptr_float(addr) = (dat); \
									} while(0)
                            
#define write_int32(dat, addr)		do { \
										ram_ptr_int32(addr) = (dat); \
									} while(0)
                            
#define write_int16(dat, addr)		do { \
										ram_ptr_int16(addr) = (dat); \
									} while(0)
                            
#define write_int8(dat, addr)		do { \
										ram_ptr_int8(addr) = (dat); \
									} while(0)

#define write_uint32(dat, addr)		do { \
										ram_ptr_uint32(addr) = (dat); \
									} while(0)

#define write_uint16(dat, addr)		do { \
										ram_ptr_uint16(addr) = (dat); \
									} while(0)

#define write_uint8(dat, addr)		do { \
										ram_ptr_uint8(addr) = (dat); \
									} while(0)

#define CARRY_FLAG         0x01
#define ZERO_FLAG          0x02
#define OVERFLOW_FLAG      0x04
#define SIGN_FLAG          0x08
#define END_OF_LOOP_FLAG   0x10
#define KERNEL_PANIC_FLAG  0x20
#define EXIT_GAME_FLAG     0x40

//#define OPER_MASK        0xE0
#define TYPE_MASK        0x3F
#define ADDR_MASK        0xC0

//#define TYPE_TERMINATE   (0 << 2)
//#define TYPE_FLOAT       (1 << 2)  // Uses big-endian format
//#define TYPE_INT32       (2 << 2)
//#define TYPE_UINT32      (3 << 2)
//#define TYPE_INT16       (4 << 2)
//#define TYPE_UINT16      (5 << 2)
//#define TYPE_INT8        (6 << 2)
//#define TYPE_UINT8       (7 << 2)

typedef enum
{
	TYPE_TERMINATE,
	TYPE_FLOAT,  // Uses big-endian format
	TYPE_INT32,
	TYPE_UINT32,
	TYPE_INT16,
	TYPE_UINT16,
	TYPE_INT8,
	TYPE_UINT8,
	TYPE_RAM_PTR,
	TYPE_STRING,
} TYPE_FLAG;

#define ADDR_IMM         (1 << 6)
#define ADDR_ABS         (2 << 6)
#define ADDR_PTR         (3 << 6)

#define ARITH_ADD        (0 << 5)
#define ARITH_SUB        (1 << 5)
#define ARITH_MUL        (2 << 5)
#define ARITH_DIV        (3 << 5)
#define ARITH_MOD        (4 << 5)
#define ARITH_POW        (5 << 5)

#define BITWISE_AND      (0 << 5)
#define BITWISE_OR       (1 << 5)
#define BITWISE_XOR      (2 << 5)
#define BITWISE_NOT      (3 << 5)
#define BITWISE_SHL      (4 << 5)
#define BITWISE_SHR      (5 << 5)

#define LOGICAL_AND      (0 << 5)
#define LOGICAL_OR       (1 << 5)
#define LOGICAL_NOT      (2 << 5)
#define LOGICAL_EQUAL    (3 << 5)
#define LOGICAL_LESS     (4 << 5)
#define LOGICAL_GREAT    (5 << 5)
#define LOGICAL_LESSEQ   (6 << 5)
#define LOGICAL_GREATEQ  (7 << 5)

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
} MEM_BUF;

#endif //__mem_access_def_h