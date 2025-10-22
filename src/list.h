#pragma once
#ifndef DYNAMIC_LISTS_H
#define DYNAMIC_LISTS_H

#include "types.h"

#define LIST_LENGTH 4096
#define LNULL -1

typedef struct tListA tFileList;
struct tListA {
    int last;
    tFile contents[LIST_LENGTH];
};

void  file_createEmpty(tFileList*);
void  file_clear(tFileList*);
void  file_add(tFileList*, tFile);
void  file_remove(tFileList*, int index);
int   file_first(tFileList);
int   file_last(tFileList);
int   file_next(tFileList, int);
int   file_prev(tFileList, int);
int   file_count(tFileList);
int   file_find_descriptor(tFileList, tDescriptor);
int   file_find_name(tFileList, tName);
tFile file_get(tFileList, int);
tFile file_createNode(tDescriptor, tMode, tName);



typedef struct tListB tCommandList;
struct tListB {
    int last;
    tCmd contents[LIST_LENGTH];
};

void cmd_createEmpty(tCommandList*);
void cmd_clear(tCommandList*);
void cmd_add(tCommandList*, tCmd);
void cmd_remove(tCommandList*, int index);
int  cmd_first(tCommandList);
int  cmd_last(tCommandList);
int  cmd_next(tCommandList, int);
int  cmd_prev(tCommandList, int);
int  cmd_count(tCommandList);
tCmd* cmd_get(tCommandList* l, int i);

#endif