#include "commands.h"

void Cmd_help(char* tr[]) {
	if (tr[1] == NULL) {
		printf("'help [cmd|-lt|-T topic|-all]' help for commands\n\tComandos disponibles:\n- authors\n- getpid\n- chdir\n- getcwd\n- date\n- hour\n- historic\n- open\n- close\n- dup\n- listopen\n- infosys\n- help\n- quit\n- exit\n- bye\n- create\n- setdirparams\n- getdirparams\n- dir\n- erase\n- delrec\n- lseek\n- writestr\n");
		return;
	}
	printf("%s ", tr[1]);

	if (!strcmp(tr[1], "authors"))  printf("%s\t%s\n", "[-n|-l]", "Prints the names and/or logins of the program authors.");

	else if (!strcmp(tr[1], "getpid"))   printf("%s\t%s\n", "[-p]", "Prints the pid of the process executing the shell or of its parent process.");

	else if (!strcmp(tr[1], "chdir"))    printf("%s\t%s\n", "[dir]", "Changes or shows the current shell directory");

	else if (!strcmp(tr[1], "getcwd"))   printf("\t%s\n", "Prints the current working directory of the shell");

	else if (!strcmp(tr[1], "date"))     printf("%s\t%s\n", "[-t|-d]", "Prints the current date in the format DD/MM/YYYY and the current time in the format hh:mm:ss.");

	else if (!strcmp(tr[1], "hour"))     printf("\t%s\n", "Prints the current time in the format hh:mm:ss.");

	else if (!strcmp(tr[1], "historic")) printf("%s\t%s\n", "[-clear|-count|-N|N]", "Shows the historic of commands executed by this shell\n\t-clear: erases the historic of commands\n\t-count: prints the size of the historic\n\t-N: shows the last N commands\n\tN: repeats the Nth command");

	else if (!strcmp(tr[1], "open"))     printf("%s\t%s\n", "fich m1 m2...", "opens the file fich, and adds it to the shell's open file list\nm1, m2.. is the mode (bitwise OR of the following)\n"
			"\tcr: O_CREAT"		"\tap: O_APPEND\n"
			"\tex: O_EXCL"		"\tro: O_RDONLY\n"
			"\trw: O_RDWR"      "\two: O_WRONLY\n"
			"\ttr: O_TRUNC");

	else if (!strcmp(tr[1], "close"))    printf("%s %s\n", "[df]", "Closes the df file descriptor and eliminates the corresponding item from the list");

	else if (!strcmp(tr[1], "dup"))      printf("%s\t%s\n", "[df]", "Duplicates the df file descriptor and adds it as a new entry to the open files list");

	else if (!strcmp(tr[1], "listopen")) printf("\t%s\n", "Lists the shell's open files");

	else if (!strcmp(tr[1], "infosys"))  printf("\t%s\n", "Prints information on the machine running the shell");

	else if (!strcmp(tr[1], "help"))     printf("%s\t%s\n", "[cmd]", "Displays a list of available commands.\ncmd: gives a brief help on the usage of comand cmd");

	else if (!strcmp(tr[1], "quit"))     printf("\t%s\n", "Ends the shell");
	else if (!strcmp(tr[1], "exit"))     printf("\t%s\n", "Ends the shell");
	else if (!strcmp(tr[1], "bye"))      printf("\t%s\n", "Ends the shell");

	else if (!strcmp(tr[1], "create"))   printf("%s\t%s\n", "[-f][name]", 	"Creates a directory or a file (-f) of name 'nam'.");

	else if (!strcmp(tr[1], "erase"))    printf("%s\t%s\n", "[n1 n2 n3 ....]", "Deletes files and/or empty directories");

	else if (!strcmp(tr[1], "writestr")) printf("%s\t%s\n", "df str", "Write the string str in the open file with descriptor df");

	else if (!strcmp(tr[1], "dir"))  	 printf("%s\t%s\n", "[-d] n1 n2 n3 ...", "Shows information for files/directories passed as argument, according to the format set in setdirparams\n\t-d: lists the contents of the parameter directories");

	else if (!strcmp(tr[1], "setdirparams"))  printf("%s\t%s\n", "[long/short][hid|nohid][lnk|nolnk][recb|reca|norec]", "Establishes parameters for listing with dir\n"
		"\t" "long|short:      long or short listing" "\n"
		"\t" " hid|nohid:      list (or not) hidden files" "\n"
		"\t" "link|nolink:     list (or not) symbolic link destination" "\n"
		"\t" "reca|recb|norec: listing recurses before (recb), before (reca) or none");

	else if (!strcmp(tr[1], "delrec"))  printf("%s\t%s\n", "n1 n2 n3 ...", "Deletes files and/or non empty directories recursively");

	else if (!strcmp(tr[1], "lseek"))  printf("%s\t%s\n", "df off ref", "Postitions the offset of an open file. ref is the reference:" "\n"
	"\t"	"SEEK_SET: beginning of the file" "\n"
	"\t"	"SEEK_CUR: current position" "\n"
	"\t"	"SEEK_END: end of the file");

	else if (!strcmp(tr[1], "getdirparams"))  printf("\t%s\n", "Shows de value of the parameters for listing with dir");
	
	else printf(" not found\n");
}