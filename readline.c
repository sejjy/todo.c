#include <stdio.h>
#include <stdlib.h>
#include "readline.h"

char *readline(void)
{
	size_t buf = 16, len = 0;
	char *str, *temp;
	int ch;

	str = malloc(buf);
	if (str == NULL)
		return NULL;

	while ((ch = getchar()) != '\n' && ch != EOF) {
		if (len + 1 >= buf) {
			buf *= 2;
			temp = realloc(str, buf);
			if (temp == NULL) {
				free(str);
				return NULL;
			}
			str = temp;
		}
		str[len++] = (char)ch;
	}
	str[len] = '\0';

	return str;
}
