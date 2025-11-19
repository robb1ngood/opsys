#include <unistd.h>
#include <errno.h>
#include "misc.h"
#include "commands.h"

ssize_t writeDescriptor(int df, void* p, size_t cont)
{
    ssize_t n;
    int aux;

    if ((n = write(df, p, cont)) == -1) {
        aux = errno;
        errno = aux;
        return -1;
    }

    return n;
}

void Cmd_write(int i, char* tr[], tFileList* fl)
{
    void* p;
    size_t cont;
    ssize_t n;

    if (i != 4) {
        fprintf(stderr, "usage: write <df> <addr> <cont>\n");
        return;
    }

    // Convert DF
    char* endptr;
    int df = (int)strtol(tr[1], &endptr, 10);
    if (*endptr != '\0') {
        fprintf(stderr, "invalid file descriptor %s\n", tr[1]);
        return;
    }

    // Convert address
    p = strtop(tr[2]);

    // Convert bytes
    cont = (size_t)strtol(tr[3], &endptr, 10);
    if (*endptr != '\0' || cont < 0) {
        fprintf(stderr, "invalid size %s\n", tr[3]);
        return;
    }

    if ((n = writeDescriptor(df, p, cont)) == -1)
        perror("Imposible escribir descriptor");
    else
        printf("wrote %lld bytes to fd %d from %p\n",
            (long long)n, df, p);
}
