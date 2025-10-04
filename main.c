//Chiara Percivaldi
//Julian Vazquez Suarez
//Mark Mucska
#include <stdio.h>
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

    for (;;) {
        tCmd command;
        printPrompt();
        readCommand(command);
        cmd_add(&commandList, command);
        executeCommand(command, &fileList, &commandList);
    }
}

void printPrompt() {
    printf("> ");
}

void readCommand(tCmd command) {
    if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL) exit(0);
}

void executeCommand(tCmd current, tFileList *fl, tCommandList *cl) {
    char *trozos[MAX_COMMAND_LENGTH];
    trocearCadena(current, trozos);

    if (!strcmp(trozos[0], "authors"))  Cmd_authors     (trozos);
    if (!strcmp(trozos[0], "getpid"))   Cmd_getpid      (trozos);
    if (!strcmp(trozos[0], "chdir"))    Cmd_chdir       (trozos);
    if (!strcmp(trozos[0], "getcwd"))   Cmd_getcwd      (trozos);
    if (!strcmp(trozos[0], "date"))     Cmd_date        (trozos);
    if (!strcmp(trozos[0], "hour"))     Cmd_hour        (trozos);
    if (!strcmp(trozos[0], "historic")) Cmd_historic    (trozos, fl, cl);
    if (!strcmp(trozos[0], "open"))     Cmd_open        (trozos, fl);
    if (!strcmp(trozos[0], "close"))    Cmd_close       (trozos, fl);
    if (!strcmp(trozos[0], "dup"))      Cmd_dup         (trozos, fl);
    if (!strcmp(trozos[0], "listopen")) Cmd_listopen    (trozos, fl);
    if (!strcmp(trozos[0], "infosys"))  Cmd_infosys     (trozos);
    if (!strcmp(trozos[0], "help"))     Cmd_help        (trozos);
    if (!strcmp(trozos[0], "quit"))     Cmd_quit        (trozos);
    if (!strcmp(trozos[0], "exit"))     Cmd_quit        (trozos);
    if (!strcmp(trozos[0], "bye"))      Cmd_quit        (trozos);
    if (!strcmp(trozos[0], "create"))   Cmd_create      (trozos);
    if (!strcmp(trozos[0], "erase"))    Cmd_erase       (trozos);
    if (!strcmp(trozos[0], "writestr")) Cmd_writestr    (trozos, fl);
}