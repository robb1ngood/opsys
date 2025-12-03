#include "commands.h"
#include <errno.h>
#include <stdlib.h>
extern char **environ;
#define MAXVAR 128

int BuscarVariable (char * var, char *e[]);
int CambiarVariable(char * var, char * valor, char *e[]);

void Cmd_envvar(int n, char *tr[], char **envp) {
	if (n == 3 && !strcmp(tr[1], "-show")) {
		int pos;
		pos = BuscarVariable(tr[2], envp);
		if (pos == -1)
			perror("envvar");
		else
			printf("envp:    %p -> %s", envp + pos, envp[pos]);
		
		pos = BuscarVariable(tr[2], environ);
		if (pos == -1)
			perror("envvar");
		else
			printf("environ: %p -> %s", environ + pos, environ[pos]);
		
		char *g = getenv(tr[2]);
		if (g == NULL)
			perror("envvar");
		else
			printf("getenv:  %p -> %s", g, g);
	}
	
	if (n == 5 && !strcmp(tr[1], "-change")) {
		if (!strcmp(tr[2], "-a"))
			CambiarVariable(tr[3], tr[4], envp);
		
		else if (!strcmp(tr[2], "-e"))
			CambiarVariable(tr[3], tr[4], environ);
		
		else if (!strcmp(tr[2], "-p")) {
			char *aux = (char *)malloc(strlen(tr[3]) + strlen(tr[4]) + 2);
			if (aux == NULL) {
				perror("envvar");
				return;
			}
			strcpy(aux, tr[3]);
			strcat(aux, "=");
			strcat(aux, tr[4]);
			putenv(aux);
			free(aux);
		}
		
		fprintf(stderr, "usage : envvar -change [-a|-e|-p] <var> <value>\n");
		return;
	}
		
	fprintf(stderr, "usage : envvar -show <var>\nusage : envvar -change [-a|-e|-p] <var> <value>\n");
}

int BuscarVariable (char * var, char *e[]) {/*busca una variable en el entorno que se le pasa como parÃ¡metro*/
	int pos = 0;                            /*devuelve la posicion de la variable en el entorno, -1 si no existe*/
	char aux[MAXVAR];
	
	strcpy (aux, var);
	strcat (aux, "=");
	
	while (e[pos] != NULL)
		if (!strncmp(e[pos], aux, strlen(aux)))
			return (pos);
		else 
			pos++;
	errno = ENOENT;   /*no hay tal variable*/
	return (-1);
}


int CambiarVariable(char * var, char * valor, char *e[]) {/*cambia una variable en el entorno que se le pasa como parÃ¡metro*/
	int pos;                                              /*lo hace directamente, no usa putenv*/
	char *aux;
	
	if ((pos = BuscarVariable(var, e)) == -1)
		return (-1);
	
	if ((aux = (char *)malloc(strlen(var) + strlen(valor) + 2)) == NULL)
		return (-1);
	strcpy(aux, var);
	strcat(aux, "=");
	strcat(aux, valor);
	e[pos]=aux;
	return (pos);
}