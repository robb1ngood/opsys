#include <unistd.h>
#include "commands.h"

void Cmd_close (char *tr[], tFileList *fl)
{
	if (tr[1]==NULL) {	/*no hay parametro*/
		Cmd_listopen(tr, fl);
		return;
	}
	
	char* endptr;
	int df = strtol(tr[1], &endptr, 10);
	if (tr[1] == endptr || df <= 2) {	/*parametro incorrecto*/
		Cmd_listopen(tr, fl);
		return;
	}
	
	int pos = file_find_descriptor(*fl, df);
	if (pos == LNULL) {
		fprintf(stderr, "Unable to close descriptor: file is not open\n");
		return;
	}
	
	if (close(df) == -1)
		perror("Unable to close descriptor");
	else
		file_remove(fl, pos);
}