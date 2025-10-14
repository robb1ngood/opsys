#define _POSIX_C_SOURCE 200809L

#include "commands.h"
#include "types.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include <limits.h>

/* Forward declarations */
static void ListarFichero(const char *path, bool longfmt, bool linkinfo);
static void ListarDirectorio(const char *dir, bool longfmt, bool linkinfo, bool showhid, tRecursiveMode recmode, int depth);

void Cmd_dir(char *tr[], dirParams *params)
{
    bool longfmt = false, linkinfo = false, showhid = false, listdirs = false;
    tRecursiveMode recmode = NOREC;

    int i = 1;
    for (; tr[i] != NULL; i++) {
        if (!strcmp(tr[i], "long")) longfmt = true;
        else if (!strcmp(tr[i], "short")) longfmt = false;
        else if (!strcmp(tr[i], "link")) linkinfo = true;
        else if (!strcmp(tr[i], "nolink")) linkinfo = false;
        else if (!strcmp(tr[i], "hid")) showhid = true;
        else if (!strcmp(tr[i], "nohid")) showhid = false;
        else if (!strcmp(tr[i], "reca")) recmode = RECA;
        else if (!strcmp(tr[i], "recb")) recmode = RECB;
        else if (!strcmp(tr[i], "norec")) recmode = NOREC;
        else if (!strcmp(tr[i], "-d")) listdirs = true;
        else break;
    }

    if (tr[i] == NULL) {
        tr[i] = ".";
        tr[i + 1] = NULL;
    }

    for (; tr[i] != NULL; i++) {
        struct stat st;
        if (lstat(tr[i], &st) == -1) {
            perror(tr[i]);
            continue;
        }

        if (S_ISDIR(st.st_mode) && listdirs)
            ListarDirectorio(tr[i], longfmt, linkinfo, showhid, recmode, 0);
        else
            ListarFichero(tr[i], longfmt, linkinfo);
    }
}

static void ListarFichero(const char *path, bool longfmt, bool linkinfo)
{
    (void)linkinfo;

    struct stat st;
    if (lstat(path, &st) == -1) {
        perror(path);
        return;
    }

    if (!longfmt) {
        printf("%-30s %10ld bytes\n", path, (long) st.st_size);
        return;
    }

    putchar(S_ISDIR(st.st_mode) ? 'd' : (S_ISLNK(st.st_mode) ? 'l' : '-'));
    putchar(st.st_mode & S_IRUSR ? 'r' : '-');
    putchar(st.st_mode & S_IWUSR ? 'w' : '-');
    putchar(st.st_mode & S_IXUSR ? 'x' : '-');
    putchar(st.st_mode & S_IRGRP ? 'r' : '-');
    putchar(st.st_mode & S_IWGRP ? 'w' : '-');
    putchar(st.st_mode & S_IXGRP ? 'x' : '-');
    putchar(st.st_mode & S_IROTH ? 'r' : '-');
    putchar(st.st_mode & S_IWOTH ? 'w' : '-');
    putchar(st.st_mode & S_IXOTH ? 'x' : '-');
    putchar(' ');

    char timebuf[64];
    struct tm *tm = localtime(&st.st_mtime);
    strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M", tm);

    printf("%3ld %8ld %s %s\n",
           (long) st.st_nlink, (long) st.st_size, timebuf, path);

    if (S_ISLNK(st.st_mode) && linkinfo) {
        char target[PATH_MAX];
        ssize_t len = readlink(path, target, sizeof(target) - 1);
        if (len != -1) {
            target[len] = '\0';
            printf(" -> %s\n", target);
        }
    }
}

static void ListarDirectorio(const char *dir, bool longfmt, bool linkinfo, bool showhid, tRecursiveMode recmode, int depth)
{
    DIR *dp;
    struct dirent *entry;
    char path[PATH_MAX];

    if ((dp = opendir(dir)) == NULL) {
        perror(dir);
        return;
    }

    if (recmode == RECA)
        printf("\n[%s]\n", dir);

    while ((entry = readdir(dp)) != NULL) {
        if (!showhid && entry->d_name[0] == '.')
            continue;

        snprintf(path, sizeof(path), "%s/%s", dir, entry->d_name);

        struct stat st;
        if (lstat(path, &st) == -1)
            continue;

        if (S_ISDIR(st.st_mode) &&
            strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..")) {

            if (recmode == RECA)
                ListarDirectorio(path, longfmt, linkinfo, showhid, recmode, depth + 1);
            else if (recmode == RECB)
                ListarDirectorio(path, longfmt, linkinfo, showhid, recmode, depth + 1);
        } else {
            ListarFichero(path, longfmt, linkinfo);
        }
    }

    closedir(dp);

    if (recmode == RECB)
        printf("\n[%s]\n", dir);
}