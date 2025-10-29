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


typedef char tCmd[MAX_COMMAND_LENGTH];


typedef enum { RECA, RECB, NOREC }  tRecursiveMode;
typedef struct {
    bool lengthFormat;
    bool linkDestination;
    bool listHidden;
    tRecursiveMode recursiveMode;
} dirParams;


typedef void*	  tMemAdress;
typedef size_t	  tMemSize;
typedef struct tm tMemTime;
typedef enum { T_MALLOC, T_SHARED, T_MAPPED } tMemType;
typedef union {
	int key;
	tFile file;
} tMemExtra;
typedef struct {
	tMemAdress adress;
	tMemSize   size;
	tMemTime   time;
	tMemType   type;
	tMemExtra  extra;
} tMem;

#endif
