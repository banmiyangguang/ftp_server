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
	char *p = strchr(str, c);
	if (p == NULL) {
		strcpy(left, str);
	} else {
		strncpy(left, str, p-str);
		strcpy(right, p+1);
	}
}

int  str_all_space(const char *str)
{
	while (*str) {
		if (!isspace(str)) {
			return 0;
		}
		str++;
	}
	return 1;
}

void str_upper(char *str)
{
	while (*str) {
		*str = toupper(*str);
		str++;
	}	
}

long long str_longlong(char *str)
{
	long long result = 0;
	long long mult = 1;
	unsigned int len = strlen(str);
	unsigned int i;

	if (len > 15) {
		return 0;
	}
	
	for (i = 0; i < len; i++) {
		char ch = str[len - (i + 1)];
		long long val;
		if (ch < '0' || ch > '9') {
			return 0;
		}
		val = ch - '0';
		result = result + val * mult;
		mult *= 10;
	}

	return result;
}

unsigned int str_octal_to_uint(const char *str)
{
	unsigned int result = 0;

	while (*str) {
		char digit = *str;
		if (!isdigit(digit) || digit > '7' || digit < '0') {
			break;
		}
		
		result = (result << 3) + (digit - '0');
		str++;
	}

	return 0;
}
