#include "commands.h"
#include <string.h>
#include <sys/wait.h>

void Cmd_deljobs(int n, char *tr[], tProcessList *pl) {
    if (n != 2 || (strcmp(tr[1], "-term") != 0 && strcmp(tr[1], "-sig") != 0)) {
        fprintf(stderr, "Usage: deljobs -term | -sig\n");
        return;
    }
    int i = process_first(*pl);
    while ( i != LNULL && i <= process_last(*pl)) {

        tProcess p = process_get(*pl, i);

        update_process_state(&p);
        process_set(pl, i, p);

        int removed = 0; // Flag to know if we removed an item

        if (strcmp(tr[1], "-term") == 0 && p.status == T_FINISHED) {
            process_remove(pl, i);
            continue; 
        }

        if (strcmp(tr[1], "-sig") == 0 && p.status == T_SIGNALED) {
            process_remove(pl, i);
            continue;
        }
        if (!removed) {
            i = process_next(*pl, i);
        }
    }
}