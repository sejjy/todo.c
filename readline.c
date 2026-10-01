#include <ctype.h>
#include <stdio.h>
#include "readline.h"

int readline(char s[], int n)
{
	int c, i = 0;

	while (isspace(c = getchar()))
		;
	while (c != '\n' && c != EOF) {
		if (i < n)
			s[i++] = c;
		c = getchar();
	}
	s[i] = '\0';

	return i;
}
