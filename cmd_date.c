#include "commands.h"
#include <time.h>

void print_hour();
void print_date();

void Cmd_date (char * tr[]) {
    if (tr[1] == NULL) {
        print_date();
        print_hour();
        return;
    }

    for (int i = 1; tr[i] != NULL; i++) {
        if (!strcmp(tr[i], "-t")) print_hour();
        if (!strcmp(tr[i], "-d")) print_date();
    }
}

void Cmd_hour (char * tr[]) {
    (void)tr;
    print_hour();
}

void print_hour() {
    time_t t;
    t = time(NULL);
    struct tm* ptr = localtime(&t);
    char str[80];
    strftime(str, sizeof(str), "%H:%M:%S", ptr);
    printf("%s\n", str);
}
void print_date() {
    time_t t;
    t = time(NULL);
    struct tm* ptr = localtime(&t);
    char str[80];
    strftime(str, sizeof(str), "%d/%m/%Y", ptr);
    printf("%s\n", str);
}
