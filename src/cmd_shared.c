#include "commands.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include "list.h"
#include "types.h"

// Finds shared memory block in the list by its key.
static int find_shared_key(tMemoryList *ml, key_t key) {
    if (ml->last == LNULL) {
        return LNULL;
    }
    for (int i = 0; i <= ml->last; i++) {
        tMem mem = mem_get(*ml, i);
        if (mem.type == T_SHARED && mem.extra.key == key) {
            return i;
        }
    }
    return LNULL;
}

// Prints all shared memory blocks.
static void list_shared_blocks(tMemoryList *ml) {
    printf("******List of shared assigned blocks for process %d\n", (int)getpid());
    char timebuff[80];
    if (ml->last == LNULL) {
        return;
    }
    for (int i = 0; i <= ml->last; i++) {
        tMem mem = mem_get(*ml, i);
        if (mem.type == T_SHARED) {
            print_mem(mem, timebuff);
            printf("\n");
        }
    }
}

// Creates a new shared memory segment, attaches it, and adds it to the list.
static void shared_create(key_t key, size_t size, tMemoryList *ml) {
    int shmid = shmget(key, size, IPC_CREAT | IPC_EXCL | 0666);

    if (shmid == -1) {
        fprintf(stderr, "Cannot create shared memory key %d: %s\n", (int)key, strerror(errno));
        return;
    }
    void *addr = shmat(shmid, NULL, 0);
    if (addr == (void *)-1) {
        fprintf(stderr, "Cannot attach shared memory key %d: %s\n", (int)key, strerror(errno));
        shmctl(shmid, IPC_RMID, NULL);
        return;
    }

    tMem mem;
    mem.adress = addr;
    mem.size = size;
    mem.type = T_SHARED;
    mem.extra.key = key;
    time_t now = time(NULL);
    mem.time = localtime(&now);

    mem_add(ml, mem);
    printf("Assigned %zu bytes at %p\n", size, addr);
}

// Attaches an existing shared memory segment.
static void shared_attach(key_t key, tMemoryList *ml) {
    if (find_shared_key(ml, key) != LNULL) {
        fprintf(stderr, "shared: key %d is already attached in this shell\n", (int)key);
        return;
    }
    int shmid = shmget(key, 0, 0);
    if (shmid == -1) {
        fprintf(stderr, "Cannot assign shared memory key %d: %s\n", (int)key, strerror(errno));
        return;
    }
    void *addr = shmat(shmid, NULL, 0);
    if (addr == (void *)-1) {
        fprintf(stderr, "Cannot assign shared memory key %d: %s\n", (int)key, strerror(errno));
        return;
    }
    struct shmid_ds buf;
    if (shmctl(shmid, IPC_STAT, &buf) == -1) {
        fprintf(stderr, "Cannot get info for shared memory key %d: %s\n", (int)key, strerror(errno));
        shmdt(addr);
        return;
    }

    tMem mem;
    mem.adress = addr;
    mem.size = buf.shm_segsz;
    mem.type = T_SHARED;
    mem.extra.key = key;
    time_t now = time(NULL);
    mem.time = localtime(&now);

    mem_add(ml, mem);
    printf("Shared memory with key %d at %p\n", (int)key, addr);
}

// Detaches a shared memory segment.
static void shared_free(key_t key, tMemoryList *ml) {
    int pos = find_shared_key(ml, key);
    if (pos == LNULL) {
        fprintf(stderr, "shared -free: key %d not found in shell's memory list\n", (int)key);
        return;
    }
    tMem mem = mem_get(*ml, pos);
    if (shmdt(mem.adress) == -1) {
        fprintf(stderr, "Cannot detach shared memory key %d: %s\n", (int)key, strerror(errno));
        return;
    }
    mem_remove(ml, pos);
}

// Removes a shared memory segment from the system.
static void shared_delkey(key_t key) {
    int shmid = shmget(key, 0, 0);
    if (shmid == -1) {
        fprintf(stderr, "Cannot get shared memory key %d: %s\n", (int)key, strerror(errno));
        return;
    }
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        fprintf(stderr, "Cannot delete shared memory key %d: %s\n", (int)key, strerror(errno));
        return;
    }
}

// Main command handler
void Cmd_shared(int n, char *tr[], tMemoryList *ml) {
    if (n == 1) {
        list_shared_blocks(ml);
        return;
    }

    char *endptr;
    key_t key;

    if (strcmp(tr[1], "-create") == 0) {
        if (n != 4) {
            fprintf(stderr, "Usage: shared -create <key> <size>\n");
            return;
        }
        key = (key_t)strtol(tr[2], &endptr, 10);
        if (*endptr != '\0') {
            fprintf(stderr, "shared: invalid key '%s'\n", tr[2]);
            return;
        }
        size_t size = (size_t)strtol(tr[3], &endptr, 10);
        if (*endptr != '\0' || size <= 0) {
            fprintf(stderr, "shared: invalid size '%s'\n", tr[3]);
            return;
        }
        shared_create(key, size, ml);
        return;
    }
    if (strcmp(tr[1], "-free") == 0) {
        if (n != 3) {
            fprintf(stderr, "Usage: shared -free <key>\n");
            return;
        }
        key = (key_t)strtol(tr[2], &endptr, 10);
        if (*endptr != '\0') {
            fprintf(stderr, "shared: invalid key '%s'\n", tr[2]);
            return;
        }
        shared_free(key, ml);
        return;
    }
    if (strcmp(tr[1], "-delkey") == 0) {
        if (n != 3) {
            fprintf(stderr, "Usage: shared -delkey <key>\n");
            return;
        }
        key = (key_t)strtol(tr[2], &endptr, 10);
        if (*endptr != '\0') {
            fprintf(stderr, "shared: invalid key '%s'\n", tr[2]);
            return;
        }
        shared_delkey(key);
        return;
    }
    if (n == 2) {
        key = (key_t)strtol(tr[1], &endptr, 10);
        if (*endptr != '\0') {
            fprintf(stderr, "Usage: shared [-create key size | -free key | -delkey key | key]\n");
            return;
        }
        shared_attach(key, ml);
        return;
    }
    fprintf(stderr, "Usage: shared [-create key size | -free key | -delkey key | key]\n");
}