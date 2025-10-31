#include "commands.h"
#include "misc.h"
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>

ssize_t LeerFichero(char *f, void *p, size_t cont)
{
	struct stat s;
	ssize_t  n;  
	int df, aux;

	if (stat(f, &s) == -1 || (df = open(f, O_RDONLY)) == -1)
		return -1;
	
	if (cont == -1)   /* si pasamos -1 como bytes a leer lo leemos entero*/
		cont = s.st_size;
		
	if ((n = read(df, p, cont)) == -1){
		aux = errno;
		close(df);
		errno = aux;
		return -1;
	}
	
	close(df);
	return n;
}

void Cmd_readfile(int i, char *tr[]) {
	void *p;
	size_t cont = -1;  /*si no pasamos tamaño se lee entero */
	ssize_t n;
	if (i < 3) {
		fprintf(stderr, "usage: readfile <file> <addr> <cont>\n");
		return;
	}
	p = strtop(tr[2]);  /*convertimos de cadena a puntero*/
	if (tr[3] != NULL) {
		char *endptr;
		cont = (size_t) strtol(tr[3], &endptr, 10);
		if(tr[3] == endptr || cont < 0)
			cont = -1;
	}

	if ((n = LeerFichero(tr[1], p, cont)) == -1)
		perror("Imposible leer fichero");
	else
		printf("read %lld bytes de %s en %p\n", (long long) n, tr[1], p);
}
