#include "commands.h"
#include "misc.h"
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>

ssize_t EscribirFichero(char *f, void *p, size_t cont)
{
	struct stat s;
	ssize_t  n;  
	int df, aux;

	if (stat(f, &s) == -1 || (df = open(f, O_WRONLY)) == -1)
		return -1;
		
	if ((n = write(df, p, cont)) == -1) {
		aux = errno;
		close(df);
		errno = aux;
		return -1;
	}
	
	close(df);
	return n;
}

void Cmd_writefile(int i, char *tr[]) {
	void *p;
	size_t cont;
	ssize_t n;
	if (i != 4) {
		fprintf(stderr, "usage: writefile <file> <addr> <cont>\n");
		return;
	}
	p = strtop(tr[2]);  /*convertimos de cadena a puntero*/
	char *endptr;
	cont = (size_t)strtol(tr[3], &endptr, 10);
	if(*endptr != '\0' || cont < 0)
		fprintf(stderr, "invalid size %s\n", tr[3]);

	if ((n = EscribirFichero(tr[1], p, cont)) == -1)
		perror("Imposible leer fichero");
	else
		printf("wrote %lld bytes to %s from %p\n", (long long) n, tr[1], p);
}
