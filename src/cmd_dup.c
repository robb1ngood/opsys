#include "commands.h"
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#define NAME_LENGHT_LIMIT PATH_MAX
void Cmd_dup (char * tr[], tFileList *fl)
{
    int df, duplicado;
    char aux[NAME_LENGHT_LIMIT];

    if (tr[1]==NULL || (df=atoi(tr[1]))<0) { /*no hay parametro*/
        Cmd_listopen(tr, fl);        /*o el descriptor es menor que 0*/
        return;
    }

    if ((duplicado = dup(df)) == -1)
        perror("imposible duplicar descriptor");
    else {
        snprintf (aux,sizeof(aux),"dup %d (%s)", df, file_get(*fl, file_find_descriptor(*fl, df)).name);
        file_add(fl, file_createNode(df, fcntl(duplicado, F_GETFL), aux));
        printf("Duplicate descriptor %d in %d\n", df, duplicado);
    }
}
