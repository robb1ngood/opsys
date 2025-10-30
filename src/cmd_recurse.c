#include "commands.h"

#define TAMANO 1024
void Recursiva (int n)
{
	char automatico[TAMANO];
	static char estatico[TAMANO];

	printf("parameter: %3d(%p) automatic array %p, static array %p\n", n, &n, automatico, estatico);

	if (n>0)
		Recursiva(n-1);
}
#undef TAMANO

void Cmd_recurse(int n, char *tr[]) {
	if(n != 2)
		fprintf(stderr, "usage: recurse <amount>\n");
	else {
		char *endptr;
		int n = strtol(tr[1], &endptr, 10);
		if(tr[1] == endptr || n <= 0) {
			fprintf(stderr, "invalid parameter\n");
			return;
		}
		
		Recursiva(n);
	}
}
