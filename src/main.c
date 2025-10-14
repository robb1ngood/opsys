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
	else perror("getcwd");
	
    printf("%s@%s{%s} %s ", sysinfo.sysname, sysinfo.nodename, cwd_trozos[i - 1], "%)");
}

void readCommand(tCmd command) {
    if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL) exit(0);
}

void executeCommand(tCmd current, tFileList *fl, tCommandList *cl, dirParams *params) {
    char *trozos[MAX_COMMAND_LENGTH];
    trocearCadena(current, trozos, " \n\t");

    if (!strcmp(trozos[0], "authors"))  Cmd_authors     (trozos);
    if (!strcmp(trozos[0], "getpid"))   Cmd_getpid      (trozos);
    if (!strcmp(trozos[0], "chdir"))    Cmd_chdir       (trozos);
    if (!strcmp(trozos[0], "getcwd"))   Cmd_getcwd      (trozos);
    if (!strcmp(trozos[0], "date"))     Cmd_date        (trozos);
    if (!strcmp(trozos[0], "hour"))     Cmd_hour        (trozos);
    if (!strcmp(trozos[0], "historic")) Cmd_historic    (trozos, fl, cl, params);
    if (!strcmp(trozos[0], "open"))     Cmd_open        (trozos, fl);
    if (!strcmp(trozos[0], "close"))    Cmd_close       (trozos, fl);
    if (!strcmp(trozos[0], "dup"))      Cmd_dup         (trozos, fl);
    if (!strcmp(trozos[0], "listopen")) Cmd_listopen    (trozos, fl);
    if (!strcmp(trozos[0], "infosys"))  Cmd_infosys     (trozos);
    if (!strcmp(trozos[0], "help"))     Cmd_help        (trozos);
    if (!strcmp(trozos[0], "quit"))     Cmd_quit        (trozos);
    if (!strcmp(trozos[0], "exit"))     Cmd_quit        (trozos);
    if (!strcmp(trozos[0], "bye"))      Cmd_quit        (trozos);

    if (!strcmp(trozos[0], "create"))       Cmd_create      (trozos);
    if (!strcmp(trozos[0], "setdirparams")) Cmd_setdirparams(trozos, params);
    if (!strcmp(trozos[0], "getdirparams")) Cmd_getdirparams(trozos, params);
    if (!strcmp(trozos[0], "dir"))          Cmd_dir         (trozos, params);
    if (!strcmp(trozos[0], "erase"))        Cmd_erase       (trozos, fl);
    if (!strcmp(trozos[0], "delrec"))       Cmd_delrec      (trozos, fl);
    if (!strcmp(trozos[0], "lseek"))        Cmd_lseek       (trozos);
    if (!strcmp(trozos[0], "writestr"))     Cmd_writestr    (trozos, fl);
}