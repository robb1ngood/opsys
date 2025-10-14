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
static void ListarFichero(const char *path, tLengthFormat, tLinkDestination);
static void ListarDirectorio(const char *dir, tLengthFormat, tLinkDestination, tListHidden, tRecursiveMode, int depth);

void Cmd_dir(char *tr[], dirParams *params)
{
	bool listdirs = (strcmp(tr[1], "-d") == 0);
	
	int i = 1;
	if(listdirs) i = 2;
    for (; tr[i] != NULL; i++) {
        struct stat st;
        if (lstat(tr[i], &st) == -1) {
            perror(tr[i]);
            continue;
        }

        if (S_ISDIR(st.st_mode) && listdirs)
            ListarDirectorio(tr[i], params->lengthFormat, params->linkDestination, params->listHidden, params->recursiveMode, 0);
        else
            ListarFichero(tr[i], params->lengthFormat, params->linkDestination);
    }
}

static void ListarFichero(const char *path, tLengthFormat longfmt, tLinkDestination linkinfo)
{
    (void)linkinfo;

    struct stat st;
	if ((linkinfo ==LINK && stat(path, &st) == -1) || (linkinfo == NOLINK && lstat(path, &st) == -1)) {
        perror(path);
        return;
    }

    if (longfmt == SHORT) {
        printf("%9ld %s \n", (long) st.st_size, path);
        return;
    }

    char timebuf[64];
    struct tm *tm = localtime(&st.st_mtime);
    strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M", tm);
	
    printf("%s %3ld ",	timebuf, (long) st.st_nlink);

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

    printf("%8ld %s\n",	(long) st.st_size, path);

    if (S_ISLNK(st.st_mode) && linkinfo) {
        char target[PATH_MAX];
        ssize_t len = readlink(path, target, sizeof(target) - 1);
        if (len != -1) {
            target[len] = '\0';
            printf(" -> %s\n", target);
        }
    }
}

static void ListarDirectorio(const char *dir, tLengthFormat longfmt, tLinkDestination linkinfo, tListHidden showhid, tRecursiveMode recmode, int depth)
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
        if (showhid == NOHID && entry->d_name[0] == '.')
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