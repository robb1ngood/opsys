#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "commands.h"
#include "list.h"

void Cmd_writestr(char *tr[], tFileList *list) {
    if (tr[1] == NULL || tr[2] == NULL) {
        fprintf(stderr, "writestr: usage writestr <descriptor> <string>\n");
        return;
    }

    int df = atoi(tr[1]);

    // check if descriptor exists in file list
    int index = file_find_descriptor(*list, df);
    if (index == LNULL) {
        fprintf(stderr, "writestr: descriptor %d not found in file list\n", df);
        return;
    }

    const char *str = tr[2];
    ssize_t written = write(df, str, strlen(str));
    if (written == -1) {
        perror("writestr");
    } else {
        printf("writestr: wrote %zd bytes to descriptor %d\n", written, df);
    }
}