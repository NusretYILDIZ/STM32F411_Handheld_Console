#ifndef __popup_h
#define __popup_h

//#define assertion(e)       ((e) ? (void)0 : _test_assertion(#e       , __FILE__, __LINE__))
//#define assertion(e, m)    ((e) ? (void)0 : _test_assertion(#e "\n" m, __FILE__, __LINE__))

void show_window_helper(const char *title, const char *msg, unsigned char color);
void show_error_window(const char *title, const char *msg);
void show_info_window(const char *title, const char *msg);
void _test_assertion(const char *e, const char *file_name, int line);

#endif //__popup_h