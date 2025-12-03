#include "list.h"
#include <stdio.h>
#include <string.h>

void process_createEmpty(tProcessList* l) {
    l->last = LNULL;
}
void process_clear		(tProcessList* l) {
    l->last = LNULL;
}
void process_add		(tProcessList* l, tProcess p) {
    if (l->last == LNULL ) {
        l->last = 0;
        l->contents[0] = p;
        return;
    }
    if (l->last + 1 >= LIST_LENGTH) {
        fprintf(stderr, "maximum number of memory blocks reached\n");
        return;
    }
    l->last++;
    l->contents[l->last] = p;
}
void process_remove		(tProcessList* l, int index) {
    if (l->last == LNULL || index < 0 || index > l->last) return;
    for (int i = index; i < l->last; i++) {
        l->contents[i] = l->contents[i + 1];
    }
    l->last--;
}

int  process_first		(tProcessList l) {
    if (l.last == LNULL) return LNULL;
    return 0;
}
int  process_last		(tProcessList l) {
    return l.last;
}
int  process_next		(tProcessList l, int i) {
    if (i + 1 <= l.last) return i + 1;
    else return LNULL;
}
int  process_prev		(tProcessList l, int i) {
    (void)l;
    if (i > 0) return i - 1;
    else return LNULL;
}
int  process_count		(tProcessList l) {
    return l.last + 1;
}

tProcess process_get	(tProcessList l, int i) {
	return l.contents[i];
}

tProcess process_createNode(pid_t pid, char **command) {
	tProcess new;
	
	new.pid = pid;
	new.time = time(NULL);
	new.status = T_ACTIVE;
	
	return new;
}
void print_process(tProcess) {
	
}