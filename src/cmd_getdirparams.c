#include "commands.h"

void Cmd_getdirparams(char *tr[], dirParams *params) {
    printf("Length format: ");
    if (params->lengthFormat == LONG)
        printf("Long\n");
    else
        printf("Short\n");

    printf("Link destination: ");
    if (params->linkDestination == LINK)
        printf("Link\n");
    else
        printf("No link\n");

    printf("List hidden: ");
    if (params->listHidden == HID)
        printf("Listed\n");
    else
        printf("Not listed\n");

    printf("Recursive mode: ");
    switch (params->recursiveMode) {
        case RECA:  printf("Contents first\n"); break;
        case RECB:  printf("Contents last\n");  break;
        case NOREC: printf("No recursion\n");   break;
    }
}