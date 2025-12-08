#include "commands.h"
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void Cmd_uid(int n, char *tr[]) {
    if (n == 1 || (n == 2 && strcmp(tr[1], "-get") == 0)) {
        uid_t real = getuid();
        uid_t eff = geteuid();
        struct passwd *pw;

        pw = getpwuid(real);
        printf("Real credential: %d, (%s)\n", real, pw ? pw->pw_name : "???");

        pw = getpwuid(eff);
        printf("Effective credential: %d, (%s)\n", eff, pw ? pw->pw_name : "???");
        return;
    }

    if (strcmp(tr[1], "-set") == 0) {
        if (n < 3) {
            printf("usage: uid -set [-l] id\n");
            return;
        }

        uid_t id;
        if (strcmp(tr[2], "-l") == 0) {
            if (n != 4) {
                printf("usage: uid -set -l login\n");
                return;
            }
            struct passwd *pw = getpwnam(tr[3]);
            if (pw == NULL) {
                printf("User %s not found\n", tr[3]);
                return;
            }
            id = pw->pw_uid;
        } else {
             if (n != 3) {
                 printf("usage: uid -set id\n");
                 return;
             }
             char *endptr;
             id = (uid_t)strtol(tr[2], &endptr, 10);
             if (*endptr != '\0') {
                 printf("Invalid id: %s\n", tr[2]);
                 return;
             }
        }
        
        if (seteuid(id) == -1) {
            perror("uid");
        }
        return;
    }
    
    printf("usage: uid [-get] | [-set [-l] id]\n");
}