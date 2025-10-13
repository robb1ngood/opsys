#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include "commands.h"

void Cmd_getcwd(char* trozos[]) {
    char cwd[PATH_MAX];

    if (trozos[1] != NULL) {
        fprintf(stderr, "getcwd: option not valid: %s\n", trozos[1]);
        return;
    }

    if (getcwd(cwd, sizeof (cwd)) != NULL) {
        printf("%s\n", cwd);
    }
    else
        perror("getcwd");
}