#include "commands.h"

void Cmd_memdump(int n, char *tr[]) {
	if (n != 3) {
		fprintf(stderr, "usage: memdump <addr> <cont>\n");
		return;
	}
	
	char *endptr;
	unsigned char *arr = (unsigned char *)strtol(tr[1], &endptr, 16);
	if (*endptr != '\0') {
		fprintf(stderr, "invalid adress %s", tr[1]);
		return;
	}
	
	size_t cont = (size_t)strtol(tr[2], &endptr, 10);
	if (*endptr != '\0') {
		fprintf(stderr, "invalid size %s", tr[2]);
		return;
	}
	
	for (size_t i = 0; i < cont; i++) {
		unsigned char c = arr[i];
		switch(c) {
			case '\n': fputs("\\n", stdout); break;
			case '\t': fputs("\\t", stdout); break;
			case '\r': fputs("\\r", stdout); break;
			default: fputc(c, stdout); break;
		}
	}
	fputc('\n', stdout);
}
