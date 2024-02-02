#ifndef __system_popup_h
#define __system_popup_h

#define test_assertion(e)   ((e) ? (void)0 : _test_assertion(#e, __FILE__, __LINE__))

void show_window_helper(const char *title, const char *msg, unsigned char color);
void show_error_window(const char *title, const char *msg);
void show_info_window(const char *title, const char *msg);
void _test_assertion(const char *e, const char *file_name, int line);

#endif //__system_popup_h