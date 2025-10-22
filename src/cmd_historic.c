#include "commands.h"
#include "main.h"
#include "trocearCadena.h"
#include <stdio.h>
#include <math.h>


void Cmd_historic(char * tr[], tFileList * fl, tCommandList * cl, dirParams *params)
{
    if (tr[1] == NULL) {
        for (int i = cmd_first(*cl);i !=LNULL && i < cmd_last(*cl); i = cmd_next(*cl, i))
            printf("%d->%s", i, *cmd_get(cl, i));
        return;
    }
    if (!strcmp(tr[1], "-clear")) {
        cmd_clear(cl);
        return;
    }
    if (!strcmp(tr[1], "-count")) {
		int count = cmd_count(*cl);
		if (count < 0) count = 0;
        printf("%d\n", cmd_count(*cl));
        return;
    }

    int N = atoi(tr[1]);
    if (N < 0) {
        int i = cmd_last(*cl) + N;
        if (i < cmd_first(*cl))
            i = cmd_first(*cl);
        for (;i != LNULL && i <= cmd_last(*cl); i = cmd_next(*cl, i))
            printf("%d->%s", i, *cmd_get(cl, i));
    }
    else
        if (N <= cmd_last(*cl) && N >= 0) {
            char* cmd = *cmd_get(cl, N);
            if(strncmp(cmd, "historic", 8) == 0) {
                fprintf(stderr, "historic: cannot re-execute 'historic' command to avoid infinite loop\n");
                return;
			}
            executeCommand(cmd, fl, cl, params);
        }
        else
            perror("command does not exist");
}