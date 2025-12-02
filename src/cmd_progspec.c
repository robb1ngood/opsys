#include "commands.h"
#include <unistd.h>

void Cmd_progspec(int n, char *tr[], tProcessList pl) {
	char **aux = calloc(n + 1, sizeof(char *));
	int i = 0;
	for (; i < n; i++) {
		if (tr[i][0] == '@' || tr[i][0] == '&') {
			aux[i] = NULL;
			break;
		}
		aux[i] = tr[i];
	}
	if (i < n && tr[i][0] == '@') {
		// change priority somehow
		i++;
	}
	if (i < n && tr[i][0] == '&') {
		// start the process in the background instead
		// add the process to background list
	}
	
	if (execvp(tr[0], aux) == -1)
		perror("execvp");
	
	free(aux);
}