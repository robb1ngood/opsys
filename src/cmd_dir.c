#define _POSIX_C_SOURCE 200809L

#include "commands.h"
#include "types.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include <limits.h>
#include <grp.h>
#include <pwd.h>

/* Forward declarations */
void ListarFichero(const char *path, tLengthFormat, tLinkDestination);
void ListarDirectorio(const char *dir, tLengthFormat, tLinkDestination, tListHidden, tRecursiveMode, int depth);

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

char LetraTF (mode_t m)
{
    switch (m&S_IFMT) { /*and bit a bit con los bits de formato,0170000 */
        case S_IFSOCK: return 's'; /*socket */
        case S_IFLNK: return 'l'; /*symbolic link*/
        case S_IFREG: return '-'; /* fichero normal*/
        case S_IFBLK: return 'b'; /*block device*/
        case S_IFDIR: return 'd'; /*directorio */ 
        case S_IFCHR: return 'c'; /*char device*/
        case S_IFIFO: return 'p'; /*pipe*/
        default: return '?'; /*desconocido, no deberia aparecer*/
    }
}

char * ConvierteModo (mode_t m, char *permisos)
{
    strcpy (permisos,"---------- ");
    
    permisos[0]=LetraTF(m);
    if (m&S_IRUSR) permisos[1]='r';    /*propietario*/
    if (m&S_IWUSR) permisos[2]='w';
    if (m&S_IXUSR) permisos[3]='x';
    if (m&S_IRGRP) permisos[4]='r';    /*grupo*/
    if (m&S_IWGRP) permisos[5]='w';
    if (m&S_IXGRP) permisos[6]='x';
    if (m&S_IROTH) permisos[7]='r';    /*resto*/
    if (m&S_IWOTH) permisos[8]='w';
    if (m&S_IXOTH) permisos[9]='x';
    if (m&S_ISUID) permisos[3]='s';    /*setuid, setgid y stickybit*/
    if (m&S_ISGID) permisos[6]='s';
    //if (m&S_ISVTX) permisos[9]='t';
    
    return permisos;
}

void ListarFichero(const char *path, tLengthFormat longfmt, tLinkDestination linkinfo)
{
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
	
	char permisos[12];
	ConvierteModo(st.st_mode, permisos);
	
	struct passwd pwd;
	struct group grp;
	pwd = *getpwuid(st.st_uid);
	grp = *getgrgid(st.st_gid);
	
    printf("%s %d %3ld %s %s %s %8ld %s\n",	timebuf, (int) st.st_ino, (long) st.st_nlink, pwd.pw_name, grp.gr_name, permisos, (long) st.st_size, path);

    if (S_ISLNK(st.st_mode) && linkinfo) {
        char target[PATH_MAX];
        ssize_t len = readlink(path, target, sizeof(target) - 1);
        if (len != -1) {
            target[len] = '\0';
            printf(" -> %s\n", target);
        }
    }
}

void ListarDirectorio(const char *dir, tLengthFormat longfmt, tLinkDestination linkinfo, tListHidden showhid, tRecursiveMode recmode, int depth)
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