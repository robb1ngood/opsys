#include "commands.h"
#include <stdlib.h>

void Cmd_lseek (char * tr[]) {
    if (tr[1] == NULL || tr[2] == NULL || tr[3] == NULL)
        perror("lseek");

    int fd = atoi(tr[1]);
    off_t off = atoi(tr[2]);
    int whence;
    if (!strcmp(tr[3], "SEEK_SET"))      whence = SEEK_SET;
    else if (!strcmp(tr[3], "SEEK_CUR")) whence = SEEK_CUR;
    else if (!strcmp(tr[3], "SEEK_END")) whence = SEEK_END;

    if(lseek(fd, off, whence) == -1)
        perror("lseek");
}