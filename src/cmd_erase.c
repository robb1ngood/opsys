#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include "commands.h"
#include "list.h"

void Cmd_erase(char *tr[], tFileList *list) {
    if (tr[1] == NULL) {
        fprintf(stderr, "erase: missing operand\n");
        return;
    }

    // n1, n2, n3...
    for (int i = 1; tr[i] != NULL; i++) {
        const char *target = tr[i];

        // Check if file is open
        int pos = file_find_name(*list, (char *) target);
        if (pos != LNULL) {
            fprintf(stderr, "erase: file '%s' is currently open (close it first)\n", target);
            continue;
        }

        // Check if file exists
        struct stat st;
        if (stat(target, &st) == -1) {
            perror("erase");
            continue;
        }

        // Deletion
        if (S_ISDIR(st.st_mode)) {
            if (rmdir(target) == -1) {
                perror("erase");
            } else {
                printf("erase: directory '%s' removed\n", target);
            }
        } else {
            if (unlink(target) == -1) {
                perror("erase");
            } else {
                printf("erase: file '%s' removed\n", target);
            }
        }
    }
}
