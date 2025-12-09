#include "commands.h"
extern char **environ;

void Cmd_showenv(int n, char *tr[], char **envp) {
	if (n == 2 && !strcmp(tr[1], "-addr")) {
		printf("environ:   %p (stored at %p)\n", environ, &environ);
		printf("main arg3: %p (stored at %p)\n", envp, &envp);
		return;
	}
	
	bool use_environ = (n == 2 && !strcmp(tr[1], "-environ"));
	char **e = (use_environ) ? environ : envp;	
	for (int i = 0; e[i] != NULL; i++)
		printf("%p->%s[%d]=(%p) %s\n", e + i, (use_environ) ? "environ" : "main arg3", i, e[i], e[i]);
}