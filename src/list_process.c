#include "list.h"
#include <stdio.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <unistd.h>
void process_createEmpty(tProcessList* l) {
    l->last = LNULL;
}
void process_clear		(tProcessList* l) {
    l->last = LNULL;
}
void process_add		(tProcessList* l, tProcess p) {
    if (l->last == LNULL ) {
        l->last = 0;
        l->contents[0] = p;
        return;
    }
    if (l->last + 1 >= LIST_LENGTH) {
        fprintf(stderr, "maximum number of memory blocks reached\n");
        return;
    }
    l->last++;
    l->contents[l->last] = p;
}
void process_remove		(tProcessList* l, int index) {
    if (l->last == LNULL || index < 0 || index > l->last) return;
    for (int i = index; i < l->last; i++) {
        l->contents[i] = l->contents[i + 1];
    }
    l->last--;
}
void process_set(tProcessList* l, int i, tProcess p) {
    if (i < 0 || i > l->last) return;
    l->contents[i] = p;
}


int  process_first		(tProcessList l) {
    if (l.last == LNULL) return LNULL;
    return 0;
}
int  process_last		(tProcessList l) {
    return l.last;
}
int  process_next		(tProcessList l, int i) {
    if (i + 1 <= l.last) return i + 1;
    else return LNULL;
}
int  process_prev		(tProcessList l, int i) {
    (void)l;
    if (i > 0) return i - 1;
    else return LNULL;
}
int  process_count		(tProcessList l) {
    return l.last + 1;
}

tProcess process_get	(tProcessList l, int i) {
	return l.contents[i];
}


tProcess process_createNode(pid_t pid, char **command) {
	tProcess new;

	new.pid = pid;
	new.time = time(NULL);
	new.status = T_ACTIVE;
	strcpy(new.command, command[0]);
    for (int i = 1; command[i] != NULL;i++) {
		strcat(new.command, " ");
		strcat(new.command, command[i]);
	}
	return new;
}

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
    else if (WIFCONTINUED(status)) {
        pl->status = T_ACTIVE;
    }

}

void print_process(tProcess p) {
    char timebuff[80];
    struct tm* tm = localtime(&p.time);
    strftime(timebuff, sizeof(timebuff), "%b %e %H:%M", tm);
    int priority = getpriority(PRIO_PROCESS, p.pid);
    printf("PID: %d | started: %s | priority: %d\n", p.pid, timebuff, priority);
    switch (p.status) {
    case T_ACTIVE:printf("ACTIVE\n"); break;
    case T_FINISHED:printf("FINISHED (exit code %d)\n", p.exitcode); break;
    case T_SIGNALED:printf("SIGNALED (signal %d)\n", p.signal); break;
    case T_STOPPED:printf("STOPPED (signal %d)\n", p.signal);  break;
    default:printf("UNKNOWN\n"); break;
    }
    printf("   Command: %s\n", p.command);
}