#include "commands.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>   // lseek
#include <fcntl.h>    // SEEK_SET, SEEK_CUR, SEEK_END

#define WRONG_ARGUMENT_ERROR { perror("lseek"); return; }

void Cmd_lseek (int n, char * tr[]) {
    if (tr[1] == NULL || tr[2] == NULL || tr[3] == NULL)
        WRONG_ARGUMENT_ERROR;
	
	char *endptr;
	
    int fd = strtol(tr[1], &endptr, 10);
	if (tr[1] == endptr) WRONG_ARGUMENT_ERROR;
	
    off_t off = strtol(tr[2], &endptr, 10);
	if (tr[2] == endptr) WRONG_ARGUMENT_ERROR;
	
    int whence;
    if (!strcmp(tr[3], "SEEK_SET"))      whence = SEEK_SET;
    else if (!strcmp(tr[3], "SEEK_CUR")) whence = SEEK_CUR;
    else if (!strcmp(tr[3], "SEEK_END")) whence = SEEK_END;
	else WRONG_ARGUMENT_ERROR;

    if(lseek(fd, off, whence) == -1)
        perror("lseek");
}

#undef WRONG_ARGUMENT_ERROR