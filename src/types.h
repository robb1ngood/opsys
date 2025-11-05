#pragma once
#ifndef OS_TYPES_H_
#define OS_TYPES_H_

#include <stdbool.h>
#include <stddef.h>
#include <time.h>

#define MAX_COMMAND_LENGTH 128
#define NAME_LENGTH_LIMIT 20

typedef char tName[NAME_LENGTH_LIMIT];
typedef struct {
    int descriptor;
    int mode;
    tName name;
} tFile;

#define print_file(file) printf("%3d %5d %s", file.descriptor, file.mode, file.name)


typedef char tCmd[MAX_COMMAND_LENGTH];


typedef enum { RECA, RECB, NOREC }  tRecursiveMode;
typedef struct {
    bool lengthFormat;
    bool linkDestination;
    bool listHidden;
    tRecursiveMode recursiveMode;
} dirParams;



typedef enum { T_MALLOC, T_SHARED, T_MAPPED } tMemType;
typedef union {
	int key;
	tFile file;
} tMemExtra;
typedef struct {
	void	  *adress;
	size_t     size;
	struct tm *time;
	tMemType   type;
	tMemExtra  extra;
} tMem;

#define print_mem(mem, timebuff) do {\
	strftime(timebuff, sizeof(timebuff), "%b %e %H:%M", mem.time);\
	printf("     %p %13zu %s ", mem.adress, mem.size, timebuff);\
	switch (mem.type) {\
		case T_MALLOC: printf("malloc"); 								break;\
		case T_SHARED: printf("shared (key %d)", mem.extra.key); 		break;\
		case T_MAPPED: printf("mapped "); print_file(mem.extra.file); 	break;\
	}\
} while(0)

#endif