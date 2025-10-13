#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include "commands.h"

void Cmd_chdir(char *trozos[]) {
    char cwd[PATH_MAX];

    if (trozos[1] == NULL) {
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("%s\n", cwd);
        } else {
            perror("chdir (getcwd)");
        }
    } else {
        if (chdir(trozos[1]) == -1) {
            perror("chdir");
        }
    }
}