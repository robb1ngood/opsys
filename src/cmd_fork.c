#include "commands.h"
#include <sys/wait.h>
#include <unistd.h>

void Cmd_fork(int n, char *tr[], tProcessList *pl) {
	pid_t pid;
	
	if ((pid=fork())==0){
		process_clear(pl);
		printf ("ejecutando proceso %d\n", getpid());
	}
	else if (pid!=-1)
		waitpid (pid,NULL,0);
}