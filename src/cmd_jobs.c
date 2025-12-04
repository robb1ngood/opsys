#include "commands.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void update_process_state(tProcess* pl) {
	int status;
	pid_t r = waitpid(pl->pid, &status, WNOHANG | WUNTRACED | WCONTINUED);
	if (r == 0) { return; }
	if (r == -1) {
		pl->status = T_FINISHED;
		return;
	}
	if (WIFEXITED(status)) {
		pl->status = T_FINISHED;
		pl->exitcode = WEXITSTATUS(status);
	}
	else if (WIFSIGNALED(status)) {
		pl->status = T_SIGNALED;
		pl->signal = WTERMSIG(status);
	}

	else if (WIFSTOPPED(status)) {
		pl->status = T_STOPPED;
		pl->signal = WSTOPSIG(status);
	}
}
void Cmd_jobs(int n, char *tr[], tProcessList *pl) {
	tProcess p;
	printf("***** Background jobs (shell pid=%d) *****\n", (int)getpid());

	for (int i = process_first(*pl); i != LNULL; i = process_next(*pl,i)) {
		p = process_get(*pl,i);
		update_process_state(&p);
		process_set(pl,i,p);
		print_process(p);
	}




}