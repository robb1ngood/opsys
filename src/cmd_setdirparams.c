#include "commands.h"

void Cmd_setdirparams(int n, char *tr[], dirParams *params) {

    if (tr[1] == NULL) {
        Cmd_getdirparams(n, tr, params);
        return;
    }

    for (int i = 1; tr[i] != NULL; i++) {
        if      (!strcmp(tr[i], "long"))   params->lengthFormat = LONG;
        else if (!strcmp(tr[i], "short"))  params->lengthFormat = SHORT;
        else if (!strcmp(tr[i], "link"))   params->linkDestination = LINK;
        else if (!strcmp(tr[i], "nolink")) params->linkDestination = NOLINK;
        else if (!strcmp(tr[i], "hid"))    params->listHidden = HID;
        else if (!strcmp(tr[i], "nohid"))  params->listHidden = NOHID;
        else if (!strcmp(tr[i], "reca"))   params->recursiveMode = RECA;
        else if (!strcmp(tr[i], "recb"))   params->recursiveMode = RECB;
        else if (!strcmp(tr[i], "norec"))  params->recursiveMode = NOREC;
    }
}