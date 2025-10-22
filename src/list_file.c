#include <string.h>
#include <stdio.h>
#include "list.h"

void  file_createEmpty  (tFileList* l) {
    l->last = LNULL;
}
void  file_clear        (tFileList* l) {
    l->last = LNULL;
}
void  file_add          (tFileList* l, tFile f)
{
    if (l->last == LNULL || l->last + 1 >= LIST_LENGTH) {
        l->last = 0;
        l->contents[0] = f;
        return;
    }

    if (l->last >= LIST_LENGTH - 1) {
        fprintf(stderr, "maximum number of open files reached\n");
        return;
    }
    for (int i = 0; i <= l->last; i++) {
        if (l->contents[i].descriptor < f.descriptor) {
            for (int j = l->last; j >= i; j++) {
                l->contents[j + 1] = l->contents[j];
            }
            l->contents[i] = f;
            l->last++;
            return;
        }
    }

    l->last++;
    l->contents[l->last] = f;
}
void  file_remove       (tFileList* l, int index) {
    if (l->last == LNULL || index < 0 || index > l->last) return;

    for (int i = index; i < l->last; i++) {
        l->contents[i] = l->contents[i + 1];
    }
    l->last--;
}

int   file_first (tFileList l) {
    if (l.last == LNULL) return LNULL;
    return 0;
}
int   file_last  (tFileList l) {
    return l.last;
}
int   file_next  (tFileList l, int i) {
    if (i + 1 < l.last) return i + 1;
    else return LNULL;
}
int   file_prev  (tFileList l, int i) {
    (void)l;
    if (i > 0) return i - 1;
    else return LNULL;
}
int   file_count (tFileList l) {
    return l.last + 1;
}

int   file_find_descriptor (tFileList l, tDescriptor df) {
    if (l.last == LNULL) return LNULL;
    for (int i = 0; i <= l.last; i++) {
        if (l.contents[i].descriptor == df) return i;
        //if (l.contents[i].descriptor > df)  return LNULL;
    }
    return LNULL;
}
int   file_find_name       (tFileList l, tName name) {
    for (int i = 0; i <= l.last; i++)
        if (!strcmp(l.contents[i].name, name)) return i;
    return LNULL;
}


tFile file_get        (tFileList l, int i) {
    return l.contents[i];
}
tFile file_createNode (tDescriptor df, tMode mode, tName name) {
    tFile file;
    file.descriptor = df;
    file.mode = mode;
    strcpy(file.name, name);
    return file;
}