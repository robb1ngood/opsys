#include "commands.h"

void Cmd_getdirparams(int n, char *tr[], dirParams *params) {
    printf("Length format: %s\nLink destination: %s\nList hidden: %s\nRecursive mode: ", params->lengthFormat ? "Long" : "Short", params->linkDestination ? "Link" : "No link", params->listHidden ? "Listed" : "Not listed");
    switch (params->recursiveMode) {
        case RECA:  printf("Contents first\n"); break;
        case RECB:  printf("Contents last\n");  break;
        case NOREC: printf("No recursion\n");   break;
    }
}