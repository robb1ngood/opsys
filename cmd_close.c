#include <unistd.h>
#include "commands.h"

void Cmd_close (char *tr[], tFileList *fl)
{
    int df;

    if (tr[1]==NULL || (df=atoi(tr[1]))<0) { /*no hay parametro, o el descriptor es menor que 0*/
        Cmd_listopen(tr, fl);
        return;
    }

    if (close(df)==-1)
        perror("Inposible cerrar descriptor");
    else {
        int pos = file_find_descriptor(*fl, df);
        if (pos != LNULL)
            file_remove(fl, pos);
        else
            perror("Inposible cerrar descriptor");
    }
}