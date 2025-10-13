#pragma once
#ifndef OS_TYPES_H_
#define OS_TYPES_H_

#define MAX_COMMAND_LENGTH 128
#define NAME_LENGTH_LIMIT 20

typedef int tDescriptor;
typedef int tMode;
typedef char tName[NAME_LENGTH_LIMIT];
typedef struct {
    tDescriptor descriptor;
    tMode mode;
    tName name;
} tFile;

typedef char tCmd[MAX_COMMAND_LENGTH];

typedef enum { LONG, SHORT } tLengthFormat;
typedef enum { LINK, NOLINK } tLinkDestination;
typedef enum { HID, NOHID } tListHidden;
typedef enum { RECA, RECB, NOREC } tRecursiveMode;
typedef struct {
    tLengthFormat lengthFormat;
    tLinkDestination linkDestination;
    tListHidden listHidden;
    tRecursiveMode recursiveMode;
} dirParams;

#endif