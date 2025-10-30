#include "commands.h"
#include "list.h"

void Cmd_listopen(int n, char * tr[], tFileList *L)
{
	(void)tr;
    int current = file_first(*L);
    while(current != LNULL) {
        tFile item = file_get(*L, current);
		print_file(item);
        printf("\n");
        current = file_next(*L, current);
    }
}