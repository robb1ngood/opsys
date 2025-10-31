/*Chiara Percivaldi*/
/*Julian Vazquez Suarez*/
/*Mark Mucska*/

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <sys/utsname.h>

#include "commands.h"
#include "list.h"
#include "misc.h"
#include "types.h"
#include "main.h"

void printPrompt();
void readCommand(tCmd);

int main(void) {
	tFileList fileList;
	file_createEmpty(&fileList);

	tCommandList commandList;
	cmd_createEmpty(&commandList);
	
	tMemoryList memList;
	mem_createEmpty(&memList);

	dirParams params = {
		false,
		false,
		false,
		NOREC
	};

	for (;;) {
		tCmd command;
		printPrompt();
		readCommand(command);
		cmd_add(&commandList, command);
		executeCommand(command, &fileList, &commandList, &memList, &params);
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

void readCommand(tCmd command) {
	if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL) exit(0);
}

#define command(name, function) else if (!strcmp(tr[0], name))  function

void executeCommand(tCmd current, tFileList *fl, tCommandList *cl, tMemoryList *ml, dirParams *params) {
	char *tr[MAX_COMMAND_LENGTH];
	int n = trocearCadena(current, tr, " \n\t");
	
	if (tr[0]==NULL)
		return;
	command("authors",  Cmd_authors )(n, tr);
	command("getpid",   Cmd_getpid  )(n, tr);
	command("chdir",    Cmd_chdir   )(n, tr);
	command("getcwd",   Cmd_getcwd  )(n, tr);
	command("date",     Cmd_date    )(n, tr);
	command("hour",     Cmd_hour    )(n, tr);
	command("historic", Cmd_historic)(n, tr, fl, cl, ml, params);
	command("open",     Cmd_open    )(n, tr, fl);
	command("close",    Cmd_close   )(n, tr, fl);
	command("dup",      Cmd_dup     )(n, tr, fl);
	command("listopen", Cmd_listopen)(n, tr, fl);
	command("infosys",  Cmd_infosys )(n, tr);
	command("help",     Cmd_help    )(n, tr);
	command("quit",     exit	    )(0);
	command("exit",     exit	    )(0);
	command("bye",      exit	    )(0);

	command("create",       Cmd_create      )(n, tr);
	command("setdirparams", Cmd_setdirparams)(n, tr, params);
	command("getdirparams", Cmd_getdirparams)(n, tr, params);
	command("dir",          Cmd_dir         )(n, tr, params);
	command("erase",        Cmd_erase       )(n, tr, fl);
	command("delrec",       Cmd_delrec      )(n, tr, fl);
	command("lseek",        Cmd_lseek       )(n, tr);
	command("writestr",     Cmd_writestr    )(n, tr, fl);
	
	command("malloc",    Cmd_malloc   )(n, tr, ml);
	command("mmap",      Cmd_mmap     )(n, tr, fl, ml);
	command("shared",    Cmd_shared   )(n, tr, ml);
	command("free",      Cmd_free     )(n, tr, ml);
	command("memfill",   Cmd_memfill  )(n, tr);
	command("memdump",   Cmd_memdump  )(n, tr);
	command("mem",       Cmd_mem      )(n, tr, ml);
	command("readfile",  Cmd_readfile )(n, tr);
	command("writefile", Cmd_writefile)(n, tr, ml);
	command("read",      Cmd_read     )(n, tr, fl, ml);
	command("write",     Cmd_write    )(n, tr, fl, ml);
	command("recurse",   Cmd_recurse  )(n, tr);
}

#undef command
