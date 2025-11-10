#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include "list.h"

void  file_createEmpty  (tFileList* l) {
	for (int i = 0; i < LIST_LENGTH; i++)
		l->hash[i] = false;
	
	// standard streams are always open
	tName in  = "stdin";
	tName out = "stdout";
	tName err = "stderr";
	file_add(l, file_createNode(0, O_RDWR | O_APPEND, in));
	file_add(l, file_createNode(1, O_RDWR | O_APPEND, out));
	file_add(l, file_createNode(2, O_RDWR | O_APPEND, err));
}
void  file_clear        (tFileList* l) {
    file_createEmpty(l);
}
void  file_add          (tFileList* l, tFile f) {
    int i = f.descriptor;
	if (i > LIST_LENGTH)
		fprintf(stderr, "invalid descriptor %d\n", i);
	l->hash[i] = true;
	l->contents[i] = f;
}
void  file_remove       (tFileList* l, int i) {
    l->hash[i] = false;
}

int   file_first (tFileList l) {
    for(int i = 0; i < LIST_LENGTH; i++)
		if (l.hash[i]) return i;
	return LNULL;
}
int   file_last  (tFileList l) {
    for(int i = LIST_LENGTH - 1; i >= 0; i--)
		if (l.hash[i]) return i;
	return LNULL;
}
int   file_next  (tFileList l, int i) {
	for(int j = i + 1; j < LIST_LENGTH; j++)
		if (l.hash[j]) return j;
	return LNULL;
}
int   file_prev  (tFileList l, int i) {
    for(int j = i - 1; j >= 0; j--)
		if (l.hash[i]) return j;
	return LNULL;
}
int   file_count (tFileList l) {
	int acc = 0;
    for (int i = 0; i < LIST_LENGTH; i++)
		acc += (int)l.hash[i];
	return acc;
}

int   file_find_descriptor (tFileList l, int df) {
    return (l.hash[df]) ? df : LNULL;
}
int   file_find_name       (tFileList l, tName name) {
    for (int i = 0; i <= LIST_LENGTH; i++)
        if (l.hash[i] && !strcmp(l.contents[i].name, name)) return i;
    return LNULL;
}


tFile file_get        (tFileList l, int i) {
    return l.contents[i];
}
tFile file_createNode (int df, int mode, tName name) {
    tFile file;
    file.descriptor = df;
    file.mode = mode;
    strcpy(file.name, name);
    return file;
}