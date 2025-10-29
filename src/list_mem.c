#include <string.h>
#include <stdio.h>
#include "list.h"

void mem_createEmpty(tMemoryList* l) {
    l->last = LNULL;
}
void mem_clear		(tMemoryList* l) {
    l->last = LNULL;
}
void mem_add		(tMemoryList* l, tMem m) {
    if (l->last == LNULL ) {
        l->last = 0;
        l->contents[0] = f;
        return;
    }
    if (l->last + 1 >= LIST_LENGTH) {
        fprintf(stderr, "maximum number of memory blocks reached\n");
        return;
    }

    for (int i = 0; i <= l->last; i++) {
        if (l->contents[i].address < m.address) {
            for (int j = l->last; j >= i; j--) {
                l->contents[j + 1] = l->contents[j];
            }
            l->contents[i] = m;
            l->last++;
            return;
        }
    }

    l->last++;
    l->contents[l->last] = f;
}
void mem_remove		(tMemoryList* l, int index) {
    if (l->last == LNULL || index < 0 || index > l->last) return;
    for (int i = index; i < l->last; i++) {
        l->contents[i] = l->contents[i + 1];
    }
    l->last--;
}

int  mem_first (tMemoryList l) {
    if (l.last == LNULL) return LNULL;
    return 0;
}
int  mem_last  (tMemoryList l) {
    return l.last;
}
int  mem_next  (tMemoryList l, int i) {
    if (i + 1 < l.last) return i + 1;
    else return LNULL;
}
int  mem_prev  (tMemoryList l, int i) {
    (void)l;
    if (i > 0) return i - 1;
    else return LNULL;
}
int  mem_count (tMemoryList l) {
    return l.last + 1;
}

tMem mem_get		(tMemoryList l, int i) {
    return l.contents[i];
}
