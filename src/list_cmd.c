#include <string.h>

#include "list.h"

void cmd_createEmpty (tCommandList* l) {
    l->last = LNULL;
}
void cmd_clear       (tCommandList* l) {
    l->last = LNULL;
}
void cmd_add         (tCommandList* l, tCmd cmd) {
    if (l->last != LNULL && l->last + 1 < LIST_LENGTH) l->last++;
    else l->last = 0;
    strcpy(l->contents[l->last], cmd);
}
void cmd_remove      (tCommandList* l, int index) {
    for (int i = index; i < l->last; i++) {
        strcpy(l->contents[i], l->contents[i + 1]);
    }
}

int  cmd_first (tCommandList l) {
    if (l.last == LNULL) return LNULL;
    return 0;
}
int  cmd_last  (tCommandList l) {
    return l.last;
}
int  cmd_next  (tCommandList l, int i) {
    if (l.last != LNULL && i < l.last && i < LIST_LENGTH) return i + 1;
    return LNULL;
}
int  cmd_prev  (tCommandList l, int i) {
    if (l.last != LNULL && i > 0 && i <= LIST_LENGTH) return i - 1;
    return LNULL;
}
int  cmd_count (tCommandList l) {
    return l.last;
}

tCmd *cmd_get(tCommandList *l, int i) {
    return &l->contents[i];
}