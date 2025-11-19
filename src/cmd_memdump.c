#include "commands.h"
#include <ctype.h>
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

	// Print hex values
	for (size_t i = 0; i < cont; i++) {
		printf("%02X ", arr[i]);
	}
	printf("\n");

	for (size_t i = 0; i < cont; i++) {
		unsigned char c = arr[i];
		switch(c) {
			case '\n': fputs("\\n ", stdout); break;
			case '\t': fputs("\\t ", stdout); break;
			case '\r': fputs("\\r ", stdout); break;
			default: if (isprint(c))
				printf("%c  ", c); // printable character
				   else
				printf("   ");//no printable character blank space
				break;
		}
	}
	fputc('\n', stdout);
}
