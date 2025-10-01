#include "commands.h"

void Cmd_help(char *tr[]) {
    if (tr[1] == NULL) {
	    printf("- %s\n- %s\n- %s\n- %s\n- %s\n- %s\n- %s\n- %s\n- %s\n- %s\n- %s\n- %s\n- %s\n- %s\n- %s\n- %s\n", "authors", "getpid", "chdir", "getcwd", "date", "hour", "historic", "open", "close", "dup", "listopen", "infosys", "help", "quit", "exit", "bye");
    	return;
    }

	if (!strcmp(tr[1], "authors"))  printf("%s\t%s\n",
		"authors", 	"Prints the names and logins of the program authors. authors -l prints only the logins and authors -n prints only the names"
		);
    
	if (!strcmp(tr[1], "getpid"))   printf("%s\t%s\n\t%s\t%s\n",
		"getpid", 	"Prints the pid of the process executing the shell.", 
		"getpid -p", 	"Prints the pid of the shell’s parent process."
		);
    
	if (!strcmp(tr[1], "chdir"))    printf("%s\t%s\n",
		"chdir [dir]", 	"Changes the current working directory of the shell to dir (using the chdir system call). When invoked without auguments it prints the current working directory (using the getcwd system call)."
		);
    
	if (!strcmp(tr[1], "getcwd"))   printf("%s\t%s\n",
		"getcwd", 	"Prints the current working directory of the shell (using the getcwd sys-tem call)."
		);
    
	if (!strcmp(tr[1], "date"))     printf("%s\t%s\n\t%s\t%s\n\t%s\t%s\n",
		"date [-t|-d]", 	"Prints the current date in the format DD/MM/YYYY and the current time in the format hh:mm:ss.", 
			"date -d", 	"Prints the current date in the format DD/MM/YYYY", 
			"date -t", 	"Prints and the current time in the format hh:mm:ss."
		);
    
	if (!strcmp(tr[1], "hour"))     printf("%s\t%s\n",
		"hour", 	"Prints and the current time in the format hh:mm:ss. (same as date -t)"
		);
    
	if (!strcmp(tr[1], "historic")) printf("%s\t%s\n\t- %s\n\t- %s\n\t- %s\n%s %s\n\t- %s\n\t- %s\n",
		"historic [N|-N]", 	"Shows the historic of commands executed by this shell. In order to do this, a list to store all the commands input to the shell must be implemented.", 
			"historic Prints all the comands that have been input with their order number", 
			"historic N Repeats command number N (from historic list)", 
			"historic -N Prints only the last N comands",
		"historic [-clear|-count]",	"Clear the historic list or report its number of elements",
			"historic -count Reports how many commands there are on the historic list",
			"historic -clear Clears the historic list"
		);
    
	if (!strcmp(tr[1], "open"))     printf("%s\n %s\n\t%s\n",
		"open [file] mode", 	"Opens a file and adds it (together with the file descriptor and the opening mode to the list of shell open files. For the mode we’ll use cr for O_CREAT, ap for O_APPEND, ex for O_EXCL, ro for O_RDONLY, rw for O_RDWR, wo for O_WRONLY and tr for O_TRUNC.",
		"Open without arguments lists the shell open files. For each file it lists its descriptor, the file name and the opening mode. The shell will inherit from its parent process its open descriptors -usually 0, 1 and 2 (stdin, stout, and stderr). To get the opening mode from a descriptor (df) we can use fcntl(fd,F GETFL)."
		);
    
	if (!strcmp(tr[1], "close"))    printf("%s\t%s\n",
		"close [df]", 	"Closes the df file descriptor and eliminates the corresponding item from the list"
		);
    
	if (!strcmp(tr[1], "dup"))      printf("%s\t%s\n",
		"dup [df]", 	"Duplicates the df file descriptor (using the dup system call, creating the corresponding new entry on the file list)"
		);
    
	if (!strcmp(tr[1], "listopen")) printf("%s\t%s\n",
		"listopen", 	"Lists the shell open files, This is the same as the open command without arguments"
		);
    
	if (!strcmp(tr[1], "infosys"))  printf("%s\t%s\n",
		"infosys", 	"Prints information on the machine running the shell (as obtained via the uname system call/library function)"
		);
    
	if (!strcmp(tr[1], "help"))     printf("%s\t%s\n",
		"help [cmd]", 	"help displays a list of available commands. help cmd gives a brief help on the usage of comand cmd"
		);
    
	if (!strcmp(tr[1], "quit"))     printf("%s\t%s\n",
		"quit", 	"Ends the shell"
		);
    
	if (!strcmp(tr[1], "exit"))     printf("%s\t%s\n",
		"exit", 	"Ends the shell"
		);
	
    if (!strcmp(tr[1], "bye"))      printf("%s\t%s\n",
		"bye", 	"Ends the shell"
		);
}