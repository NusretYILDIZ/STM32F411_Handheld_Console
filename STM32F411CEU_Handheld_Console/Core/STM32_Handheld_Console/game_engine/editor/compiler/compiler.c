#include "./compiler.h"
#include <string.h>

uint8_t parentheses_balanced(char *src)
{
	uint32_t char_index = 0,
			 src_len = strlen(src);
	
	int16_t parenthesis_balance = 0,
			array_def_balance = 0;
	
	uint8_t string_literal_mode = 0;
	
	while(char_index < src_len)
	{
		if(!string_literal_mode)
		{
			if(src[char_index] == '#')
			{
				while(src[char_index] != '\n') char_index++;
			}
			else if(src[char_index] == '(') parenthesis_balance++;
			else if(src[char_index] == ')') parenthesis_balance--;
			else if(src[char_index] == '[') array_def_balance++;
			else if(src[char_index] == ']') array_def_balance--;
			
			else if(src[char_index] == '"') string_literal_mode = 1;
		}
		else
		{
			     if(src[char_index] == '"') string_literal_mode = 0;
			else if(src[char_index] == '\\') char_index++;  // Escape character, ignore it.
		}
		
		char_index++;
	}
	
	if(string_literal_mode)
	{
		show_error_window("Compiler", "Missing string close mark '\"'");
		return 0;
	}
	
	if(parenthesis_balance > 0)
	{
		show_error_window("Compiler", "Missing parenthesis close mark ')'");
		return 0;
	}
	else if(parenthesis_balance < 0)
	{
		show_error_window("Compiler", "Unnecessary parenthesis close mark ')'");
		return 0;
	}
	
	if(array_def_balance > 0)
	{
		show_error_window("Compiler", "Missing array definition close mark ']'");
		return 0;
	}
	else if(array_def_balance < 0)
	{
		show_error_window("Compiler", "Unnecessary array definition close mark ']'");
		return 0;
	}
	
	show_info_window("Compiler", "Parentheses are balanced.");
	return 1;
}

uint8_t compile(char *src, char *bin)
{
	if(!parentheses_balanced(src))
	{
		show_error_window("Compiler", "Compilation failed.");
		return 1;
	}
}