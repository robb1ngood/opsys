#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include "commands.h"
#include "list.h"

void delete_recursive(const char *target, tFileList *list) {
    // Check if file is open
    int pos = file_find_name(*list, (char *) target);
    if (pos != LNULL) {
        fprintf(stderr, "delrec: file '%s' is currently open (close it first)\n", target);
        return;
    }

    // Check if file exists
    struct stat st;
    if (lstat(target, &st) == -1) {
        perror("delrec");
        return;
    }

     // Deletion
    if (S_ISDIR(st.st_mode)) {
        DIR *dir = opendir(target);
        if (!dir) {
            perror("delrec");
            return;
        }

        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;

            // Build full path
            char path[PATH_MAX];
            snprintf(path, sizeof(path), "%s/%s", target, entry->d_name);

            // Recurse
            delete_recursive(path, list);
        }

        closedir(dir);

        // Remove the directory
        if (rmdir(target) == -1) {
            perror("delrec");
        } else {
            printf("delrec: directory '%s' removed\n", target);
        }
    } else {
        // Remove file
        if (unlink(target) == -1) {
            perror("delrec");
        } else {
            printf("delrec: file '%s' removed\n", target);
        }
    }
}

void Cmd_delrec(int n, char *tr[], tFileList *list) {
    if (tr[1] == NULL) {
        fprintf(stderr, "delrec: missing operand\n");
        return;
    }

    // n1, n2, n3...
    for (int i = 1; tr[i] != NULL; i++) {
        delete_recursive(tr[i], list);
    }
}