#ifndef __instructions_h
#define __instructions_h

#define INST_TABLE(X)   X(0x00,        syscall) \
                        X(0x01,         assign) \
                        X(0x02,     arith_calc) \
                        X(0x03,        bitwise) \
                        X(0x04,        logical) \
                        X(0x05,            jsr) \
                        X(0x06,            rts) \
                        X(0x07,        jump_if) \
                        X(0x08,           jump) \
                        X(0x09,           exit) \
                        X(0x0a,  set_text_area) \
                        X(0x0b,     set_cursor) \
                        X(0x0c, set_text_color) \
                        X(0x0d,  set_text_size) \
                        X(0x0e,  set_text_wrap) \
                        X(0x0f,       set_font) \
                        X(0x10,      print_chr) \
                        X(0x11,      print_str) \
                        X(0x12,      print_int) \
                        X(0x13,     printf_str) \
                        X(0x14,     draw_image) \
                        X(0x15,       load_prg) \
                        X(0x16,        mem_set) \
                        X(0x17, update_display)

#define INST_DECLARE(opc, ins)  void vm_inst_##ins(void);
INST_TABLE(INST_DECLARE)
#undef INST_DECLARE

#endif //__instructions_h