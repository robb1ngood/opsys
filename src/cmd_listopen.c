#include "commands.h"
#include "list.h"

void Cmd_listopen(int n, char * tr[], tFileList *L)
{
	(void)tr;
    int current = file_first(*L);
    while(current != LNULL) {
        tFile item = file_get(*L, current);
        printf("%3d %5d %s\n", item.descriptor, item.mode, item.name);
        current = file_next(*L, current);
    }
}