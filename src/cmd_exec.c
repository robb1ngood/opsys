#include "commands.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/resource.h>
#include <errno.h>

void Cmd_exec(int n, char *tr[]) {
    
    if (tr[1] == NULL) {
        fprintf(stderr, "exec: missing operand\n");
        return;
    }

    char **argv_exec = malloc((n) * sizeof(char *));
    if (!argv_exec) {
        perror("exec");
        return;
    }

    int priority = 0;
    int set_prio = 0;
    int i;
    int j = 0;

    for (i = 1; i < n && tr[i] != NULL; i++) {
        if (tr[i][0] == '@' || tr[i][0] == '&') {
            break;
        }
        argv_exec[j++] = tr[i];
    }
    argv_exec[j] = NULL;

    if (i < n && tr[i] != NULL && tr[i][0] == '@') {
        char *endptr;
        priority = (int)strtol(tr[i] + 1, &endptr, 10);
        if (*endptr == '\0') {
            set_prio = 1;
        } else {
            fprintf(stderr, "exec: invalid priority %s\n", tr[i]);
            free(argv_exec);
            return;
        }
    }

    if (set_prio) {
        if (setpriority(PRIO_PROCESS, 0, priority) == -1) {
            perror("exec: setpriority");
        }
    }

    execvp(argv_exec[0], argv_exec);

    if (errno == ENOENT && strchr(argv_exec[0], '/') == NULL) {
        char *original_name = argv_exec[0];
        char *local_path = malloc(strlen(original_name) + 3);
        
        if (local_path) {
            sprintf(local_path, "./%s", original_name);
            argv_exec[0] = local_path;
            execvp(argv_exec[0], argv_exec);
            free(local_path);
            argv_exec[0] = original_name;
        }
    }
    perror("exec");
    
    free(argv_exec);
}