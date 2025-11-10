#include "commands.h"
#include <sys/mman.h>
#include <sys/shm.h>
#include <errno.h>

void Cmd_free(int n, char *tr[], tFileList *fl, tMemoryList *ml) {
	if(tr[1] == NULL) {
		fprintf(stderr, "usage: free <adress>\n");
		return;
	}
	
	char *endptr;
	void *p = (void *)strtol(tr[1], &endptr, 16);
	if (*endptr != '\0') {
		fprintf(stderr, "invalid adress %s", tr[1]);
		return;
	}
	
	tMem mem;
	int i;
	for (i = mem_first(*ml); i != LNULL; i = mem_next(*ml, i))
		if ((mem = mem_get(*ml, i)).adress == p)
			break;
	
	switch (mem.type) {
		case T_MALLOC:
			free(mem.adress);
			break;
		case T_MAPPED:
			if(munmap(mem.adress, mem.size) == -1) {
				perror("unmap");
				return;
			}
			file_remove(fl, file_find_descriptor(*fl, mem.extra.file.descriptor));
			break;
		case T_SHARED:
			if (shmdt(mem.adress) == -1) {
				fprintf(stderr, "Cannot detach shared memory key %d: %s\n", (int)mem.extra.key, strerror(errno));
				return;
			}
			break;
	}
	mem_remove(ml, i);
}
