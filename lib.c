#include <ctype.h>

int is_cint(int c) {
	if (isdigit(c) || c == '.' || c == ',' || c == '\n' || c == '-') return 1;
	return 0;
}

int is_int(char *str) {
	char *sptr = str;

	while (*sptr) {
		if (!is_cint(*sptr)) return 0;
		sptr++;
	}
	return 1;
}

char *del_sym(char *str, int sym) {
	static char out[256];
	char *optr = out;

	while (*str) {
		if (*str != sym) {
			*optr = *str;
			optr++;
		}
		str++;
	}
	*optr = '\0';

	return out;
}
