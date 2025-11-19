#include "commands.h"
#include "misc.h"
#include <unistd.h>
#include <errno.h>

ssize_t ReadDescriptor(int df, void* p, size_t cont)
{
    ssize_t n;
    int aux;

    if ((n = read(df, p, cont)) == -1) {
        aux = errno;
        errno = aux;
        return -1;
    }
    return n;
}
void Cmd_read(int i, char* tr[], tFileList* fl)
{
    void* p;
    size_t cont = -1;
    ssize_t n;
    int df;
    char* endptr;

    if (i < 3) {
        fprintf(stderr, "usage: read <df> <addr> <cont>\n");
        return;
    }

    df = (int)strtol(tr[1], &endptr, 10);
    if (tr[1] == endptr) {
        fprintf(stderr, "invalid file descriptor %s\n", tr[1]);
        return;
    }

    p = strtop(tr[2]);   /*convertimos de cadena a puntero*/

    int pos = file_find_descriptor(*fl, df);
    if (pos == LNULL) {
        fprintf(stderr, "Impossibile read file: Bad file descriptor\n");
        return;
    }

    if (tr[3] != NULL) {
        cont = (size_t)strtol(tr[3], &endptr, 10);
        if (tr[3] == endptr || cont < 0)
            cont = -1;
    }

    if ((n = ReadDescriptor(df, p, cont)) == -1)
        perror("Imposible leer descriptor");
    else
        printf("read %lld bytes del descriptor %d en %p\n",
            (long long)n, df, p);
}
