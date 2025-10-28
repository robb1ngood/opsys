#include "commands.h"

void Cmd_open(int n, char* tr[], tFileList* list) {
	int i, df, mode = 0;

	if (tr[1] == NULL) { /*no hay parametro*/
		Cmd_listopen(n, tr, list);
		return;
	}
	for (i = 2; tr[i] != NULL; i++)
		if (!strcmp(tr[i], "cr")) mode |= O_CREAT;
		else if (!strcmp(tr[i], "ex")) mode |= O_EXCL;
		else if (!strcmp(tr[i], "ro")) mode |= O_RDONLY;
		else if (!strcmp(tr[i], "wo")) mode |= O_WRONLY;
		else if (!strcmp(tr[i], "rw")) mode |= O_RDWR;
		else if (!strcmp(tr[i],"ap")) mode|=O_APPEND;
		else if (!strcmp(tr[i],"tr")) mode|=O_TRUNC;
		else {
			fprintf(stderr, "open: invalid mode '%s'\n", tr[i]);
			return; 
		}

	df = open(tr[1], mode, 0777);
	if (df==-1){ 
		perror("Imposible abrir fichero");
		return;
	}
		
	else{
		file_add(list, file_createNode(df, mode, tr[1]));
		printf ("Anadida entrada a la tabla ficheros abiertos. nombre: %s, modo: %d, descriptor: %d\n",tr[1], mode, df);
	}
}