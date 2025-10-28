#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "commands.h"

void Cmd_getpid(int n, char* trozos[]) {
    if (trozos[1] == NULL) {
        printf("%d\n", (int)getpid());
    }
    else if (strcmp(trozos[1], "-p") == 0) {
        printf("%d\n", (int)getppid());
    }
    else {
        fprintf(stderr, "getpid: invalid option '%s'\n", trozos[1]);
    }
}