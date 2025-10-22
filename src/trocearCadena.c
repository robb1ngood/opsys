#include "trocearCadena.h"
int trocearCadena(tCmd cadena, char * trozos[], char *separators)
{
    int i ;
    trozos[0] = strtok(cadena, separators);
    if (trozos[0] == NULL)
        return 0;
        for (i = 1; i < MAX_COMMAND_LENGTH - 1; i++) {
			trozos[i] = strtok(NULL, separators);
			if (trozos[i] == NULL)
                break;
    }

    trozos[i]=NULL;
    return i;
}