#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include "commands.h"

void Cmd_erase(char *trozos[]) {
    if (trozos[1] == NULL) {
        fprintf(stderr, "erase: missing operand\n");
        return;
    }

    for (int i = 1; trozos[i] != NULL; i++) {
        struct stat st;
        if (stat(trozos[i], &st) == -1) {
            perror("erase");
            continue;
        }

        if (S_ISDIR(st.st_mode)) {
            if (rmdir(trozos[i]) == -1) {
                perror("erase");
            }
        } else {
            if (unlink(trozos[i]) == -1) {
                perror("erase");
            }
        }
    }
}