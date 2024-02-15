#ifndef __inst_table_h
#define __inst_table_h

#define INST_TABLE(X)   X(0x00,    syscall) \
                        X(0x01,     assign) \
						X(0x02, arith_calc) \
						X(0x03,    bitwise) \
						X(0x04,    logical) \
						X(0x05,        jsr) \
						X(0x06,        rts) \
						X(0x07,    jump_if) \
						X(0x08,       jump) \
						X(0x09,       exit)

#define TYPE_FLOAT       (0 << 2)
#define TYPE_INT8        (1 << 2)
#define TYPE_INT16       (2 << 2)
#define TYPE_INT32       (3 << 2)
#define TYPE_UINT8       (4 << 2)
#define TYPE_UINT16      (5 << 2)
#define TYPE_UINT32      (6 << 2)

#define ADDR_IMM         (0 << 0)
#define ADDR_ABS         (1 << 0)
#define ADDR_PTR         (2 << 0)

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

#endif //__inst_table_h