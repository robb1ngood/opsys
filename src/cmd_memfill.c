#include "commands.h"

void Cmd_memfill(int n, char *tr[]) {
	if (n != 4) {
		fprintf(stderr, "usage: memfill <addr> <cont> <char>\n");
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
	
	unsigned char byte = tr[3][0];	

	for (size_t i = 0; i < cont; i++)
		arr[i]=byte;
}
