#ifndef OS_MISC_H
#define OS_MISC_H

#include <string.h>
int trocearCadena(char *cadena, char *tr[], const char *separators);

void *strtop(const char* s);

#include <sys/stat.h>
char *ConvierteModo(mode_t m, char *permisos);

#endif