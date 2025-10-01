#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include "commands.h"

void Cmd_create(char *trozos[]) {
    if (trozos[1] == NULL) {
        fprintf(stderr, "create: missing operand\n");
        return;
    }

    if (strcmp(trozos[1], "-f") == 0) {
        if (trozos[2] == NULL) {
            fprintf(stderr, "create: missing file name\n");
            return;
        }
        int fd = creat(trozos[2], 0644);
        if (fd == -1) {
            perror("create");
        } else {
            close(fd);
        }
    } else {
        if (mkdir(trozos[1], 0755) == -1) {
            perror("create");
        }
    }
}