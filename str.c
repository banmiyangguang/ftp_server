#include "str.h"
#include "common.h"

void str_trim_crlf(char *str)
{
	char *p = &str[strlen(str) - 1];
	while (*p == '\r' || *p == '\n')
	{
		*p-- = '\0';
	}
}

void str_split(const char *str, char *left, char *right, char c)
{

}

int  str_all_space(const char *str)
{
	return 0;
}

void str_upper(char *str)
{
	
}

long long str_longlong(char *str)
{
	return 0;
}

unsigned int str_octal_to_uint(const char *str)
{
	return 0;
}
