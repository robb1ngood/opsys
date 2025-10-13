#ifndef OS_FILE_H
#define OS_FILE_H

#include <stddef.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "types.h"

#include "list.h"

void Cmd_authors     (char * tr[]);
void Cmd_getpid      (char * tr[]);
void Cmd_chdir       (char * tr[]);
void Cmd_getcwd      (char * tr[]);
void Cmd_date        (char * tr[]);
void Cmd_hour        (char * tr[]);
void Cmd_historic    (char * tr[], tFileList *fl, tCommandList *cl, dirParams *params);
void Cmd_open        (char * tr[], tFileList *list);
void Cmd_close       (char * tr[], tFileList *list);
void Cmd_dup         (char * tr[], tFileList *list);
void Cmd_listopen    (char * tr[], tFileList *list);
void Cmd_infosys     (char * tr[]);
void Cmd_help        (char * tr[]);
void Cmd_quit        (char * tr[]);

void Cmd_create      (char * tr[]);
void Cmd_setdirparams(char *tr[], dirParams *params);
void Cmd_getdirparams(char *tr[], dirParams *params);
void Cmd_dir         (char * tr[]);
void Cmd_erase       (char *tr[], tFileList *list);
void Cmd_delrec      (char *tr[], tFileList *list);
void Cmd_lseek       (char * tr[]);
void Cmd_writestr    (char *tr[], tFileList *list);

#endif