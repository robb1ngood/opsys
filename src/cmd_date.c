#include "commands.h"
#include <time.h>

#define print_time(buff, ptr) do { strftime(buff, sizeof(buff), "%H:%M:%S", ptr); printf("%s\n", buff); } while(0)
#define print_date(buff, ptr) do { strftime(buff, sizeof(buff), "%d/%m/%Y", ptr); printf("%s\n", buff); } while(0)

void Cmd_date(int n, char *tr[]) {
	char buff[80];
	time_t t = time(NULL);
	struct tm *ptr = localtime(&t);
	
	if (tr[1] == NULL) {
		print_date(buff, ptr);
		print_time(buff, ptr);
	}

	for (int i = 1; tr[i] != NULL && i <= 2; i++) {
		if (!strcmp(tr[i], "-t")) print_time(buff, ptr);
		if (!strcmp(tr[i], "-d")) print_date(buff, ptr);
	}
}

void Cmd_hour(int n, char *tr[]) {
	char buff[80];
	time_t t = time(NULL);
	struct tm *ptr = localtime(&t);
	
	print_time(buff, ptr);
}