#include "commands.h"

#define help(cmd, args, text) else if (!strcmp(tr[1], cmd)) printf("%s %s\t%s\n", cmd, args, text)

void Cmd_help(int n, char* tr[]) {
	if (tr[1] == NULL) {
		printf("'help [cmd|-lt|-T topic|-all]' help for commands\n\tComandos disponibles:\n- authors\n- getpid\n- chdir\n- getcwd\n- date\n- hour\n- historic\n- open\n- close\n- dup\n- listopen\n- infosys\n- help\n- quit\n- exit\n- bye\n- create\n- setdirparams\n- getdirparams\n- dir\n- erase\n- delrec\n- lseek\n- writestr\n");
		return;
	}

	help("authors",  "[-n|-l]", "Prints the names and/or logins of the program authors.");
	help("getpid",   "[-p]", 	"Prints the pid of the process executing the shell or of its parent process.");
	help("chdir",    "[dir]", 	"Changes or shows the current shell directory");
	help("getcwd", 	 "",		"Prints the current working directory of the shell");
	help("date",     "[-t|-d]", "Prints the current date in the format DD/MM/YYYY and the current time in the format hh:mm:ss.");
	help("hour", 	 "",		"Prints the current time in the format hh:mm:ss.");
	help("open", 	 "", 		"Opens the file fich, and adds it to the shell's open file list\nopen [name] and the mode (bitwise OR of the following)\n\tcr: O_CREAT\tap: O_APPEND\n\tex: O_EXCL\tro: O_RDONLY\n\trw: O_RDWR\two: O_WRONLY\n\ttr: O_TRUNC");
	help("close", 	 "[df]", 	"Closes the df file descriptor and eliminates the corresponding item from the list");
	help("dup", 	 "[df]", 	"Duplicates the df file descriptor and adds it as a new entry to the open files list");
	help("listopen", "",	 	"Lists the shell's open files");
	help("infosys",  "",		"Prints information on the machine running the shell");
	help("help", 	 "[cmd]", 	"Displays a list of available commands.\ncmd: gives a brief help on the usage of comand cmd");
	help("quit",	 "", 		"Ends the shell");
	help("exit",	 "", 		"Ends the shell");
	help("bye",		 "", 		"Ends the shell");
	help("historic", "[-clear|-count|-N|N]", "Shows the historic of commands executed by this shell\n\t-clear: erases the historic of commands\n\t-count: prints the size of the historic\n\t-N: shows the last N commands\n\tN: repeats the Nth command");

	help("create", 		 "[-f][name]",		  "Creates a directory or a file (-f) of name 'nam'.");
	help("erase",  		 "n1 n2 n3 ....", 	  "Deletes files and/or empty directories");
	help("writestr", 	 "df str", 			  "Write the string str in the open file with descriptor df");
	help("dir", 		 "[-d] n1 n2 n3 ...", "Shows information for files/directories passed as argument, according to the format set in setdirparams\n\t-d: lists the contents of the parameter directories");
	help("delrec", 		 "n1 n2 n3 ...", 	  "Deletes files and/or non empty directories recursively");
	help("lseek", 		 "df off ref", 		  "Postitions the offset of an open file. ref is the reference:\n\tSEEK_SET: beginning of the file\n\tSEEK_CUR: current position\n\tSEEK_END: end of the file");
	help("getdirparams", "",				  "Shows de value of the parameters for listing with dir");
	help("setdirparams", "[long/short][hid|nohid][lnk|nolnk][recb|reca|norec]", "Establishes parameters for listing with dir\n\tlong|short:      long or short listing\n\t hid|nohid:      list (or not) hidden files\n\tlink|nolink:     list (or not) symbolic link destination\n\treca|recb|norec: listing recurses before (recb), before (reca) or none");
	
	help("malloc", 		"[-free][n]", 		 "assigns a memory block of size n\n\t-ferr: deassigns a memory block of size n");
	help("mmap", 		"[-free] fich perm", "maps the file fich with perm permissions to memory\n\t-free fich: unmaps the file fich");
	help("free", 		"adr", 				 "deallocates the memory block at the adr adress");
	help("memfill", 	"addr n ch", 		 "fills n characters in memory with ch starting from the adress addr");
	help("memdump", 	"addr n", 			 "Dumps the contents of n bytes of memory starting at address addr to the screen");
	help("readfile", 	"fich addr n", 		 "reads n bytes from fich to addr");
	help("writefile", 	"fich addr n", 		 "writes n bytes to fich from addr");
	help("read", 		"df addr n", 		 "reads n bytes from df to addr");
	help("write", 		"df addr n", 		 "writes n bytes to df from addr");
	help("recurse", 	"[n]", 				 "calls the recursive function n times");
	help("shared", 		"[-free|-create|-delkey] cl [n]", 	 "manages shared memory of key cl\n\t-create cl n: Creates a block of shared memory with key cl and size n and attaches it to the process address space\n\tcl: Attaches a block of shared memory with key cl to the process address space\n\t-free cl: Detaches a block of shared memory of key cl\n\t-delkey cl: Removes de memory block of key cl from the system (without unmapping)");
	help("mem", 		"[-blocks|-funcs|-vars|-all|-pmap]", "Shows details of the process memory\n\t-blocks: memory blocks assigned\n\t-funcs: function addresses\n\t-vars: variable addresses\n\t-pmap: shows pmap command output\n\t-all: shows everything");
	
	else printf("%s not found\n", tr[1]);
}