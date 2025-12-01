#ifndef OS_FILE_H
#define OS_FILE_H

#include <stddef.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "types.h"

#include "list.h"

#define defCmd(name, ...) void name (int, char *[], __VA_ARGS__)

defCmd (Cmd_authors);
defCmd (Cmd_getpid);
defCmd (Cmd_chdir);
defCmd (Cmd_getcwd);
defCmd (Cmd_date);
defCmd (Cmd_hour);
defCmd (Cmd_historic, 	tFileList*, tCommandList*, tMemoryList*, dirParams*, char **envp);
defCmd (Cmd_open,     	tFileList*);
defCmd (Cmd_close,    	tFileList*);
defCmd (Cmd_dup,      	tFileList*);
defCmd (Cmd_listopen, 	tFileList*);
defCmd (Cmd_infosys);
defCmd (Cmd_help);

defCmd (Cmd_create);
defCmd (Cmd_setdirparams, 	dirParams*);
defCmd (Cmd_getdirparams, 	dirParams*);
defCmd (Cmd_dir, 			dirParams*);
defCmd (Cmd_erase, 			tFileList*);
defCmd (Cmd_delrec, 		tFileList*);
defCmd (Cmd_lseek);
defCmd (Cmd_writestr, 		tFileList*);

defCmd (Cmd_malloc,      tMemoryList*);
defCmd (Cmd_mmap,        tFileList*, tMemoryList*);
defCmd (Cmd_shared,      tMemoryList*);
defCmd (Cmd_free,        tFileList*, tMemoryList*);
defCmd (Cmd_memfill);
defCmd (Cmd_memdump);
defCmd (Cmd_mem,         tMemoryList*);
defCmd (Cmd_readfile);
defCmd (Cmd_writefile);
defCmd (Cmd_read,        tFileList*);
defCmd (Cmd_write,       tFileList*);
defCmd (Cmd_recurse);

defCmd (Cmd_uid);
defCmd (Cmd_envvar, 	char **envp);
defCmd (Cmd_showenv, 	char **envp);
defCmd (Cmd_fork);
defCmd (Cmd_exec);
defCmd (Cmd_jobs, 		tProcessList);
defCmd (Cmd_deljobs, 	tProcessList);
defCmd (Cmd_progspec, 	tProcessList);

#undef defCmd

#endif