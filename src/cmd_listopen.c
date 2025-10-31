#include "commands.h"
#include "list.h"

void Cmd_listopen(int n, char * tr[], tFileList *L)
{
	for (int i = file_first(*L); i != LNULL && i < file_last(*L); i = file_next(*L, i)) {
		print_file(file_get(*L, i));
		printf("\n");
	}
}  