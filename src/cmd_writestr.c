#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "commands.h"
#include "list.h"

void Cmd_writestr(int n, char *tr[], tFileList *list) {
    if (tr[1] == NULL || tr[2] == NULL) {
        fprintf(stderr, "writestr: usage writestr <descriptor> <string>\n");
        return;
    }

	char *endptr;
    int df = strtol(tr[1], &endptr, 10);
	if (tr[1] == endptr) {
		fprintf(stderr, "writestr: descriptor must be a number\n");
		return;
	}

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