#include "commands.h"
#include <sys/wait.h>
#include <unistd.h>


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