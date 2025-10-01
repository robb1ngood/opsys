#include <stdio.h>
#include <string.h>
#include "commands.h"

typedef struct{
    const char* name;
    const char* login;

}strAuthor;

static const strAuthor AUTHORS[] = {
    {"Chiara Percivaldi", "chiara.percivaldi@udc.es"},
    {"Julian Vazquez Suarez", "julian.vazquez.suarez@udc.es" },
    {"Mark Mucska", "mark.mucska@udc.es" },
};

static const size_t NUM_AUTHORS = sizeof(AUTHORS) / sizeof(strAuthor);

void Cmd_authors(char* trozos[]) {
    if (trozos[1] == NULL) {
        for (size_t i = 0; i < NUM_AUTHORS; i++) {
            printf("%s %s\n", AUTHORS[i].name, AUTHORS[i].login);
        }
    }
    else if (strcmp(trozos[1],"-l") == 0) {
        for (size_t i = 0; i < NUM_AUTHORS; i++) {
            printf("%s\n", AUTHORS[i].login);
        }
    }
    else if (strcmp(trozos[1],"-n") == 0) {
        for (size_t i = 0; i < NUM_AUTHORS; i++) {
            printf("%s\n", AUTHORS[i].name);
        }
    }
    else{
        fprintf(stderr, "authors: option no valid: %s\n", trozos[1]);
    }
}