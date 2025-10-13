#include "commands.h"
#include "main.h"
#include "trocearCadena.h"
#include <math.h>

void Cmd_historic(char * tr[], tFileList * fl, tCommandList * cl, dirParams *params)
{
    if (tr[1] == NULL) {
        for (int i = cmd_first(*cl); i < cmd_last(*cl); i = cmd_next(*cl, i))
            printf("%d) %s\n", i, *cmd_get(cl, i));
        return;
    }
    if (!strcmp(tr[1], "-clear")) {
        cmd_clear(cl);
        return;
    }
    if (!strcmp(tr[1], "-count")) {
        printf("%d\n", cmd_count(*cl));
        return;
    }

    int N = atoi(tr[1]);
    if (N < 0) {
        int i = cmd_last(*cl) + N;
        if (i < cmd_first(*cl))
            i = cmd_first(*cl);
        for (; i < cmd_last(*cl); i = cmd_next(*cl, i))
            printf("%d) %s\n", i, *cmd_get(cl, i));
    }
    else
        if (N <= cmd_last(*cl))
            executeCommand(*cmd_get(cl, N), fl, cl, params);
        else
            perror("command does not exist");
}