#pragma once
#ifndef DYNAMIC_LISTS_H
#define DYNAMIC_LISTS_H

#include "types.h"

#define LIST_LENGTH 4096
#define LNULL -1

typedef struct tListA tFileList;
struct tListA {
    bool  hash[LIST_LENGTH];
    tFile contents[LIST_LENGTH];
};

void  file_createEmpty	  (tFileList*);
void  file_clear		  (tFileList*);
void  file_add			  (tFileList*, tFile);
void  file_remove		  (tFileList*, int i);
int   file_first		  (tFileList);
int   file_last			  (tFileList);
int   file_next			  (tFileList,  int i);	// i must be a valid position. Returns LNULL if it ends oob
int   file_prev			  (tFileList,  int i);	// i must be a valid position. Returns LNULL if it ends oob
int   file_count		  (tFileList);
int   file_find_descriptor(tFileList,  int df);
int   file_find_name	  (tFileList,  tName);
tFile file_get			  (tFileList,  int);
tFile file_createNode	  (int, int, tName);



typedef struct tListB tCommandList;
struct tListB {
    int last;
    tCmd contents[LIST_LENGTH];
};

void cmd_createEmpty(tCommandList*);
void cmd_clear		(tCommandList*);
void cmd_add		(tCommandList*, tCmd);
void cmd_remove		(tCommandList*, int index);
int  cmd_first		(tCommandList);
int  cmd_last		(tCommandList);
int  cmd_next		(tCommandList, int);	// i must be a valid position. Returns LNULL if it ends oob
int  cmd_prev		(tCommandList, int);	// i must be a valid position. Returns LNULL if it ends oob
int  cmd_count		(tCommandList);
tCmd* cmd_get		(tCommandList* l, int i);



typedef struct tListC tMemoryList;
struct tListC {
	int last;
	tMem contents[LIST_LENGTH];
};

void mem_createEmpty(tMemoryList*);
void mem_clear		(tMemoryList*);
void mem_add		(tMemoryList*, tMem);
void mem_remove		(tMemoryList*, int);
int  mem_first		(tMemoryList);
int  mem_last		(tMemoryList);
int  mem_next		(tMemoryList, int);		// i must be a valid position. Returns LNULL if it ends oob
int  mem_prev		(tMemoryList, int);		// i must be a valid position. Returns LNULL if it ends oob
int  mem_count		(tMemoryList);
tMem mem_get		(tMemoryList, int);

tMem mem_createNode(void *adress, size_t size, time_t time, tMemType type, void *extra);
void print_mem(tMem mem);



typedef struct tListD tProcessList;
struct tListD {
		int last;
		tProcess contents[LIST_LENGTH];
};

void process_createEmpty(tProcessList*);
void process_clear		(tProcessList*);
void process_add		(tProcessList*, tProcess);
void process_remove		(tProcessList*, int);
int  process_first		(tProcessList);
int  process_last		(tProcessList);
int  process_next		(tProcessList, int);		// i must be a valid position. Returns LNULL if it ends oob
int  process_prev		(tProcessList, int);		// i must be a valid position. Returns LNULL if it ends oob
int  process_count		(tProcessList);
tProcess process_get	(tProcessList, int);

tProcess process_createNode(pid_t pid, time_t time, tProcessStatus status, tCmd command, int priority);
void print_process(tProcess);


#endif