#include "trocearCadena.h"
int trocearCadena(tCmd cadena, char * trozos[], char *separators)
{
    int i = 1;
    if ((trozos[0] = strtok(cadena, separators)) == NULL)
        return 0;
    while ((trozos[i] = strtok(NULL, separators)) != NULL)
        i++;
    return i;
}