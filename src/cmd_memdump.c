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
	if (*endptr != '\0' || cont < 0) {
		fprintf(stderr, "invalid size %s", tr[2]);
		return;
	}
	
	for (size_t i = 0; i < cont; i += 20) {
		printf("%p->  ", arr + i);
		for(size_t j = i; j < (i + 20) && j < cont; j++) {
			unsigned char c = arr[j];
			switch(c) {
				case '\n': printf("\\n "); break;
				case '\t': printf("\\t "); break;
				case '\r': printf("\\r "); break;
				default: printf("%2c ", c);
			}
		}
		printf("\n%p->  ", arr + i);
		for (size_t j = i; j < (i + 20) && j < cont; j++) {
			unsigned char c = arr[j];
			printf("%02x ", c);
		}
		fputc('\n', stdout);
	}
}
