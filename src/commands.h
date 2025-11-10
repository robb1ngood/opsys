#ifndef OS_FILE_H
#define OS_FILE_H

#include <stddef.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "types.h"

#include "list.h"

void Cmd_authors     (int, char *tr[]);
void Cmd_getpid      (int, char *tr[]);
void Cmd_chdir       (int, char *tr[]);
void Cmd_getcwd      (int, char *tr[]);
void Cmd_date        (int, char *tr[]);
void Cmd_hour        (int, char *tr[]);
void Cmd_historic    (int, char *tr[], tFileList*, tCommandList*, tMemoryList*, dirParams*);
void Cmd_open        (int, char *tr[], tFileList*);
void Cmd_close       (int, char *tr[], tFileList*);
void Cmd_dup         (int, char *tr[], tFileList*);
void Cmd_listopen    (int, char *tr[], tFileList*);
void Cmd_infosys     (int, char *tr[]);
void Cmd_help        (int, char *tr[]);

void Cmd_create      (int, char *tr[]);
void Cmd_setdirparams(int, char *tr[], dirParams*);
void Cmd_getdirparams(int, char *tr[], dirParams*);
void Cmd_dir         (int, char *tr[], dirParams*);
void Cmd_erase       (int, char *tr[], tFileList*);
void Cmd_delrec      (int, char *tr[], tFileList*);
void Cmd_lseek       (int, char *tr[]);
void Cmd_writestr    (int, char *tr[], tFileList*);

void Cmd_malloc      (int, char *tr[], tMemoryList*);
void Cmd_mmap        (int, char *tr[], tFileList*, tMemoryList*);
void Cmd_shared      (int, char *tr[], tMemoryList*);
void Cmd_free        (int, char *tr[], tFileList*, tMemoryList*);
void Cmd_memfill     (int, char *tr[]);
void Cmd_memdump     (int, char *tr[]);
void Cmd_mem         (int, char *tr[], tMemoryList*);
void Cmd_readfile    (int, char *tr[]);
void Cmd_writefile   (int, char *tr[]);
void Cmd_read        (int, char *tr[], tFileList*);
void Cmd_write       (int, char *tr[], tFileList*);
void Cmd_recurse     (int, char *tr[]);

#endif