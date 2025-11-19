#include "commands.h"
#include <unistd.h>

void aux_alloc(size_t n, tMemoryList *ml);
void aux_dealloc(size_t n, tMemoryList *ml);

void Cmd_malloc(int l, char *tr[], tMemoryList *ml) {
	size_t n;
	char *endptr;
	
	if(tr[1] != NULL) {
		
		if(!strcmp("-free", tr[1]) && tr[2] != NULL) {
			n = strtol(tr[2], &endptr, 10);
			if(*endptr != '\0' || n <= 0) {
				fprintf(stderr, "malloc: invalid size %s\n", tr[2]);
				return;
			}
			aux_dealloc(n, ml);
			return;
		}
		
		//else
		n = strtol(tr[1], &endptr, 10);
		if(*endptr != '\0' || n <= 0) {
			fprintf(stderr, "malloc: invalid size %s\n", tr[1]);
			return;
		}
		aux_alloc(n, ml);
		return;
	}
	
	printf("******List of mapped blocks for process %d\n", (int)getpid());
	tMem mem;
	for(int i = mem_first(*ml); i != LNULL; i = mem_next(*ml, i)) {
		if((mem = mem_get(*ml, i)).type != T_MALLOC)
			continue;
		print_mem(mem);
		printf("\n");
	}
	return;
}

void aux_alloc(size_t n, tMemoryList *ml) {
	void *p = malloc(n);
	if(p == NULL) {
		perror("malloc");
		return;
	}	
	printf("malloc: assigned %zu bytes at %p\n", n, p);

	tMem node = mem_createNode(p, n, time(NULL), T_MALLOC, NULL);
	mem_add(ml, node);
}
void aux_dealloc(size_t n, tMemoryList *ml) {
	tMem mem;
	for(int i = mem_first(*ml); i != LNULL; i = mem_next(*ml, i)) {
		mem = mem_get(*ml, i);
		if(mem.type == T_MALLOC && mem.size == n) {
			free(mem.adress);
			mem_remove(ml, i);
			return;
		}
	}
	printf("no memory block of size %zu is assigned\n", n);
}