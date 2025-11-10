#include "commands.h"
#include "list.h"
#include <unistd.h>
#include <fcntl.h>

void Cmd_listopen(int n, char * tr[], tFileList *L)
{
	for (int i = file_first(*L); i != LNULL; i = file_next(*L, i)) {
		tFile f = file_get(*L, i);
		printf("descriptor: %d, offset: (%2ld)->%s", f.descriptor, lseek(f.descriptor, 0, SEEK_CUR), f.name);
		if (f.mode & O_CREAT)  printf(" O_CREAT");
		if (f.mode & O_APPEND) printf(" O_APPEND");
		if (f.mode & O_EXCL)   printf(" O_EXCL");
		if (f.mode & O_WRONLY) printf(" O_WRONLY");
		if (f.mode & O_RDONLY) printf(" O_RDONLY");
		if (f.mode & O_RDWR)   printf(" O_RDWR");
		if (f.mode & O_TRUNC)  printf(" O_TRUNC");
		printf("\n");
	}
}