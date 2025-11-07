#include "commands.h"
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>

void free_file(char *file);
void *map_file(char *file, int protection, tFileList*, tMemoryList*);

void Cmd_mmap(int n, char *tr[], tFileList *fl, tMemoryList *ml) {
	void *p;
	char *perm;
	int protection;
	
	if (tr[1] != NULL) {
		
		if (!strcmp(tr[1], "-free")) {
			if(tr[2] != NULL)
				free_file(tr[2]);
			else
				fprintf(stderr, "usage: mmap -free <mapped file name>\n");
			return;
		}
		
		//else
		protection = PROT_NONE;
		if ((perm = tr[2]) != NULL && strlen(perm) < 4) {
			if (strchr(perm, 'r') != NULL) protection |= PROT_READ;
			if (strchr(perm, 'w') != NULL) protection |= PROT_WRITE;
			if (strchr(perm, 'x') != NULL) protection |= PROT_EXEC;
		}
		if((p = map_file(tr[1], protection, fl, ml)) == NULL)
			perror("mmap");
		else
			printf("file %s mapped at adress %p\n", tr[1], p);
		return;
	}
	
	printf("******List of mapped blocks for process %d\n", (int)getpid());
	tMem mem;
	for(int i = mem_first(*ml); i != LNULL && i <= mem_last(*ml); i = mem_next(*ml, i)) {
		if((mem = mem_get(*ml, i)).type != T_MAPPED)
			continue;
		print_mem(mem);
		printf("\n");
	}
	return;
}


void free_file(char *file) {
	fprintf(stderr, "freeing memory not implemented\n");
}
void *map_file(char *file, int protection, tFileList *fl, tMemoryList *ml) {
	
	int df, map = MAP_PRIVATE, modo = O_RDONLY;
	struct stat s;
	void *p;
	
	if (protection & PROT_WRITE)
		modo = O_RDWR;
	if (stat(file, &s) == -1 || (df = open(file, modo)) == -1)
		return NULL;
	if ((p = mmap(NULL, s.st_size, protection, map, df, 0)) == MAP_FAILED)
		return NULL;
	
	tFile f = file_createNode(df, modo, file);
	tMem  m = mem_createNode(p, s.st_size, time(NULL), T_MAPPED, (void *)&f);
	
	file_add(fl, f);
	mem_add(ml, m);
	
	return p;
}
