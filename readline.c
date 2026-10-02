#include <ctype.h>
#include <stdio.h>
#include "readline.h"

int read_line(char *str, int len)
{
	int ch, num_chars = 0;

	while (isspace(ch = getchar()))
		;
	while (ch != '\n' && ch != EOF) {
		if (num_chars < len)
			str[num_chars++] = ch;
		ch = getchar();
	}
	str[num_chars] = '\0';

	return num_chars;
}
