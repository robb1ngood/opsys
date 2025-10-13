#include <stdio.h>
#include <string.h>
#include <sys/utsname.h>
#include "commands.h"

void Cmd_infosys(char *trozos[]) {
    struct utsname sysinfo;

    if (trozos[1] != NULL) {
        fprintf(stderr, "infosys: option not valid: %s\n", trozos[1]);
        return;
    }

    if (uname(&sysinfo) == -1) {
        perror("infosys (uname)");
        return;
    }

    printf("System name:    %s\n", sysinfo.sysname);
    printf("Node name:      %s\n", sysinfo.nodename);
    printf("Release:        %s\n", sysinfo.release);
    printf("Version:        %s\n", sysinfo.version);
    printf("Machine:        %s\n", sysinfo.machine);
#ifdef _GNU_SOURCE
    printf("Domain name:    %s\n", sysinfo.domainname);
#endif
}