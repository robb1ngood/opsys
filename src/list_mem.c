#include "list.h"

void mem_createEmpty(tMemoryList*) {}
void mem_clear		(tMemoryList*) {}
void mem_add		(tMemoryList*, tMem) {}
void mem_remove		(tMemoryList*, int) {}
int  mem_first		(tMemoryList) {}
int  mem_last		(tMemoryList) {}
int  mem_next		(tMemoryList, int) {}
int  mem_prev		(tMemoryList, int) {}
int  mem_count		(tMemoryList) {}
tMem mem_get		(tMemoryList, int) {}
