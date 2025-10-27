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
#include "trocearCadena.h"
#include "types.h"
#include "main.h"

void printPrompt();
void readCommand(tCmd);

int main(void) {
	tFileList fileList;
	file_createEmpty(&fileList);

	tCommandList commandList;
	cmd_createEmpty(&commandList);

	dirParams params = {
		SHORT,
		NOLINK,
		NOHID,
		NOREC
	};

	for (;;) {
		tCmd command;
		printPrompt();
		readCommand(command);
		cmd_add(&commandList, command);
		executeCommand(command, &fileList, &commandList, &params);
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
	trocearCadena(current, tr, " \n\t");
	
	if (tr[0]==NULL)
		return;
	command("authors",  Cmd_authors )(tr);
	command("getpid",   Cmd_getpid  )(tr);
	command("chdir",    Cmd_chdir   )(tr);
	command("getcwd",   Cmd_getcwd  )(tr);
	command("date",     Cmd_date    )(tr);
	command("hour",     Cmd_hour    )(tr);
	command("historic", Cmd_historic)(tr, fl, cl, ml, params);
	command("open",     Cmd_open    )(tr, fl);
	command("close",    Cmd_close   )(tr, fl);
	command("dup",      Cmd_dup     )(tr, fl);
	command("listopen", Cmd_listopen)(tr, fl);
	command("infosys",  Cmd_infosys )(tr);
	command("help",     Cmd_help    )(tr);
	command("quit",     Cmd_quit    )(tr);
	command("exit",     Cmd_quit    )(tr);
	command("bye",      Cmd_quit    )(tr);

	command("create",       Cmd_create      )(tr);
	command("setdirparams", Cmd_setdirparams)(tr, params);
	command("getdirparams", Cmd_getdirparams)(tr, params);
	command("dir",          Cmd_dir         )(tr, params);
	command("erase",        Cmd_erase       )(tr, fl);
	command("delrec",       Cmd_delrec      )(tr, fl);
	command("lseek",        Cmd_lseek       )(tr);
	command("writestr",     Cmd_writestr    )(tr, fl);
	
	command("malloc",    Cmd_malloc   )(tr, ml);
	command("mmap",      Cmd_mmap     )(tr, fl, ml);
	command("shared",    Cmd_shared   )(tr, ml);
	command("free",      Cmd_free     )(tr, ml);
	command("memfill",   Cmd_memfill  )(tr);
	command("memdump",   Cmd_memdump  )(tr);
	command("mem",       Cmd_mem      )(tr, ml);
	command("readfile",  Cmd_readfile )(tr, ml);
	command("writefile", Cmd_writefile)(tr, ml);
	command("read",      Cmd_read     )(tr, fl, ml);
	command("write",     Cmd_write    )(tr, fl, ml);
	command("recurse",   Cmd_recurse  )(tr);
}

#undef command