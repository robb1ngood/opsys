#include "commands.h"

void Cmd_setdirparams(int n, char *tr[], dirParams *p) {

    if (tr[1] == NULL) {
        Cmd_getdirparams(n, tr, p);
        return;
    }

    for (int i = 1; tr[i] != NULL; i++) {
        if      (!strcmp(tr[i], "long"))   p->lengthFormat = true;
        else if (!strcmp(tr[i], "short"))  p->lengthFormat = false;
        else if (!strcmp(tr[i], "link"))   p->linkDestination = true;
        else if (!strcmp(tr[i], "nolink")) p->linkDestination = false;
        else if (!strcmp(tr[i], "hid"))    p->listHidden = true;
        else if (!strcmp(tr[i], "nohid"))  p->listHidden = false;
        else if (!strcmp(tr[i], "reca"))   p->recursiveMode = RECA;
        else if (!strcmp(tr[i], "recb"))   p->recursiveMode = RECB;
        else if (!strcmp(tr[i], "norec"))  p->recursiveMode = NOREC;
		else fprintf(stderr, "usage: setdirparams [long|short][link|nolink][hid|nohid][reca|recb|norec]");
    }
}