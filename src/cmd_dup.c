#include "commands.h"
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>


void Cmd_dup (int n, char * tr[], tFileList *fl)
{
	if (tr[1]==NULL) { /*no hay parametro*/
		Cmd_listopen(n, tr, fl);
		return;
	}
	
	char *endptr, aux[PATH_MAX];
	int df = strtol(tr[1], &endptr, 10), duplicado;
	if (tr[1] == endptr || df < 0) {/*parametro invalido*/
		Cmd_listopen(n, tr, fl);	/*o el descriptor es menor que 0*/
		return;
	}

	if ((duplicado = dup(df)) == -1)
		perror("imposible duplicar descriptor");
	else {
		int pos = file_find_descriptor(*fl, df);
		if (pos == LNULL) {
			fprintf(stderr, "imposible duplicar descriptor");
			return;
		}
		snprintf(aux, sizeof(aux), "dup %d (%s)", df, file_get(*fl, pos).name);
		file_add(fl, file_createNode(duplicado, fcntl(duplicado, F_GETFL), aux));
		printf("Duplicate descriptor %d in %d\n", df, duplicado);
	}
}
