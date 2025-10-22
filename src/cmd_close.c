#include <unistd.h>
#include "commands.h"

void Cmd_close (char *tr[], tFileList *fl)
{
	if (tr[1]==NULL) {	/*no hay parametro*/
		Cmd_listopen(tr, fl);
		return;
	}
	
	char **endptr;
	int df = strtol(tr[1], endptr, 10);
	if (tr[1] == *endptr || df < 0) { /*parametro invalido, o el descriptor es menor que 0*/
		Cmd_listopen(tr, fl);
		return;
	}
	
	if (df == 0 || df == 1 || df == 2) {
		fprintf(stderr, "It is not allowed to close stdin/stdout/stderr.\n");
		return;
	}
	int pos = file_find_descriptor(*fl, df);
	if (pos == LNULL) {
		perror("Unable to close descriptor");
		return;
	}
	
	if (close(df) == -1)
		perror("Unable to close descriptor");
	else
		file_remove(fl, pos);
}