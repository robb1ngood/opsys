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
	time_t     time;
	tMemType   type;
	tMemExtra  extra;
} tMem;



typedef enum { T_FINISHED, T_STOPPED, T_SIGNALED, T_ACTIVE } tProcessStatus;
typedef struct {
	pid_t  pid;
	time_t time;
	tProcessStatus status;
	tCmd command;
	int priority;
} tProcess;

#endif