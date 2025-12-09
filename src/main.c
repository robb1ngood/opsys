/*Chiara Percivaldi*/
/*Julian Vazquez Suarez*/
/*Mark Mucska*/

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <sys/utsname.h>

// necesary for deleting the memory once done
#include <sys/mman.h>
#include <sys/shm.h>

#include "commands.h"
#include "list.h"
#include "misc.h"
#include "types.h"
#include "main.h"

void  printPrompt();
char* readCommand(tCmd);
void  quitOut(tMemoryList*);

int main(int argc, char *argv[], char **envp) {
	
	tFileList 	 fileList; 	  file_createEmpty(&fileList);
	tCommandList commandList; cmd_createEmpty (&commandList);
	tMemoryList  memList; 	  mem_createEmpty (&memList);
	tProcessList processList; process_createEmpty(&processList);
	dirParams params = { false, false, false, NOREC };

	for (;;) {
		tCmd command;
		printPrompt();
		if (readCommand(command) == NULL) {
			quitOut(&memList);
		}
		cmd_add(&commandList, command);
		executeCommand(command, &fileList, &commandList, &memList, &processList, &params, envp);
	}
}

void printPrompt() {
	struct utsname sysinfo;
	if (uname(&sysinfo) == -1) {
		perror("(uname)");
		return;
	}
	
	char cwd[PATH_MAX];
	char *cwd_trozos[PATH_MAX];
	int i;
	if (getcwd(cwd, sizeof (cwd)) != NULL)
		i = trocearCadena(cwd, cwd_trozos, "\\/");
	else {
		perror("getcwd");
		return;
	}
	
	printf("%s@%s{%s} %%) ", sysinfo.sysname, sysinfo.nodename, cwd_trozos[i - 1]);
}
char* readCommand(tCmd command) {
	return fgets(command, MAX_COMMAND_LENGTH, stdin);
}
void quitOut(tMemoryList *ml) {
	for(int i = mem_first(*ml); i != LNULL; i = mem_next(*ml, i)) {
		tMem mem = mem_get(*ml, i);
		switch (mem.type) {
			case T_MALLOC: free(mem.adress);			 break;
			case T_MAPPED: munmap(mem.adress, mem.size); break;
			case T_SHARED: shmdt(mem.adress);			 break;
		}
	}
	exit(0);
}

#define command(name, function, ...) else if (!strcmp(tr[0], name))  function(__VA_ARGS__)

void executeCommand(tCmd current, tFileList *fl, tCommandList *cl, tMemoryList *ml, tProcessList *pl, dirParams *params, char **envp) {
	char *tr[MAX_COMMAND_LENGTH];
	int n = trocearCadena(current, tr, " \n\t");
	
	if (tr[0]==NULL)
		return;
	command("authors",  Cmd_authors,  n, tr);
	command("getpid",   Cmd_getpid,	  n, tr);
	command("chdir",    Cmd_chdir,	  n, tr);
	command("getcwd",   Cmd_getcwd,	  n, tr);
	command("date",     Cmd_date,	  n, tr);
	command("hour",     Cmd_hour,	  n, tr);
	command("historic", Cmd_historic, n, tr, fl, cl, ml, pl, params, envp);
	command("open",     Cmd_open,	  n, tr, fl);
	command("close",    Cmd_close,	  n, tr, fl);
	command("dup",      Cmd_dup,	  n, tr, fl);
	command("listopen", Cmd_listopen, n, tr, fl);
	command("infosys",  Cmd_infosys,  n, tr);
	command("help",     Cmd_help,	  n, tr);
	command("quit",     quitOut,	  ml);
	command("exit",     quitOut,	  ml);
	command("bye",      quitOut,	  ml);

	command("create",       Cmd_create,		  n, tr);
	command("setdirparams", Cmd_setdirparams, n, tr, params);
	command("getdirparams", Cmd_getdirparams, n, tr, params);
	command("dir",          Cmd_dir,		  n, tr, params);
	command("erase",        Cmd_erase,		  n, tr, fl);
	command("delrec",       Cmd_delrec,		  n, tr, fl);
	command("lseek",        Cmd_lseek,		  n, tr);
	command("writestr",     Cmd_writestr,	  n, tr, fl);
	
	command("malloc",    Cmd_malloc,	n, tr, ml);
	command("mmap",      Cmd_mmap,		n, tr, fl, ml);
	command("shared",    Cmd_shared,	n, tr, ml);
	command("free",      Cmd_free,		n, tr, fl, ml);
	command("memfill",   Cmd_memfill,	n, tr);
	command("memdump",   Cmd_memdump,	n, tr);
	command("mem",       Cmd_mem,		n, tr, ml);
	command("readfile",  Cmd_readfile,	n, tr);
	command("writefile", Cmd_writefile,	n, tr);
	command("read",      Cmd_read,		n, tr, fl);
	command("write",     Cmd_write,		n, tr, fl);
	command("recurse",   Cmd_recurse,	n, tr);
	command("showenv", Cmd_showenv, n, tr, envp);
	command("envvar", 	Cmd_envvar, 	n, tr, envp);
	command("jobs", 	Cmd_jobs, 		n, tr, pl);
	command("deljobs",  Cmd_deljobs, 	n, tr, pl);
	command("uid",      Cmd_uid,       	n, tr);
	command("exec",		Cmd_exec,		n, tr);
	else Cmd_progspec(n, tr, pl);
}

#undef command
