#ifndef OS_FILE_H
#define OS_FILE_H

#include <stddef.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "types.h"

#include "list.h"

void Cmd_authors     (char *tr[]);
void Cmd_getpid      (char *tr[]);
void Cmd_chdir       (char *tr[]);
void Cmd_getcwd      (char *tr[]);
void Cmd_date        (char *tr[]);
void Cmd_hour        (char *tr[]);
void Cmd_historic    (char *tr[], tFileList*, tCommandList*, tMemoryList*, dirParams*);
void Cmd_open        (char *tr[], tFileList*);
void Cmd_close       (char *tr[], tFileList*);
void Cmd_dup         (char *tr[], tFileList*);
void Cmd_listopen    (char *tr[], tFileList*);
void Cmd_infosys     (char *tr[]);
void Cmd_help        (char *tr[]);
void Cmd_quit        (char *tr[]);

void Cmd_create      (char *tr[]);
void Cmd_setdirparams(char *tr[], dirParams*);
void Cmd_getdirparams(char *tr[], dirParams*);
void Cmd_dir         (char *tr[], dirParams*);
void Cmd_erase       (char *tr[], tFileList*);
void Cmd_delrec      (char *tr[], tFileList*);
void Cmd_lseek       (char *tr[]);
void Cmd_writestr    (char *tr[], tFileList*);

void Cmd_malloc      (char *tr[], tMemoryList*);
void Cmd_mmap        (char *tr[], tFileList*, tMemoryList*);
void Cmd_shared      (char *tr[], tMemoryList*);
void Cmd_free        (char *tr[], tMemoryList*);
void Cmd_memfill     (char *tr[]);
void Cmd_memdump     (char *tr[]);
void Cmd_mem         (char *tr[], tMemoryList*);
void Cmd_readfile    (char *tr[], tMemoryList*);
void Cmd_writefile   (char *tr[], tMemoryList*);
void Cmd_read        (char *tr[], tFileList*, tMemoryList*);
void Cmd_write       (char *tr[], tFileList*, tMemoryList*);
void Cmd_recurse     (char *tr[]);

#endif