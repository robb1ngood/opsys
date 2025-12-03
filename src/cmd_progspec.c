#include "commands.h"
#include <unistd.h>
#include <limits.h>
#include <sys/resource.h>
#include <sys/wait.h>

void Cmd_progspec(int n, char *tr[], tProcessList *pl) {
	char **aux = calloc(n + 1, sizeof(char *));
	int priority = getpriority(PRIO_PROCESS, 0);
	bool is_bg = false;
	int i = 0;
	for (; i < n; i++) {
		if (tr[i][0] == '@' || tr[i][0] == '&') {
			aux[i] = NULL;
			break;
		}
		aux[i] = tr[i];
	}
	if (i < n && tr[i][0] == '@') {
		char *endptr;
		priority = strtol(&(tr[i][1]), &endptr, 10);
		if (*endptr != '0') {
			fprintf(stderr, "invalid priority\n");
			return;
		}
		i++;
	}
	if (i < n && tr[i][0] == '&') {
		is_bg = true;
	}
	
	//duplicate the calling process. This will become the child process later
	pid_t pid;
	if ((pid = fork()) == 0) {
		char path[PATH_MAX];
		getcwd(path, sizeof(path));
		strcat(path, "/");
		strcat(path, tr[0]);
		setpriority(PRIO_PROCESS, 0, priority);
		execvp(path, aux);
		perror(path);
		exit(0);		
	}
	else {
		if (is_bg)
			process_add(pl, process_createNode(pid, aux));
		else
			waitpid(pid, NULL, 0);
		free(aux);
	}
}