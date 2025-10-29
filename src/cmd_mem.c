#include "commands.h"
#include <stdio.h>

#define print_funcs(p1, p2, p3, l1, l2, l3) do {\
	printf("Program functions: %p, %p, %p\nLibrary functions: %p, %p, %p\n", p1, p2, p3, l1, l2, l3);\
} while(0)
	
#define print_vars(e1, e2, e3, ei1, ei2, ei3, s1, s2, s3, si1, si2, si3, a1, a2, a3) do {\
	printf("Variables:\n");\
	printf(" -External:             %p, %p, %p\n", &e1, &e2, &e3);\
	printf(" -External initialized: %p, %p, %p\n", &ei1, &ei2, &ei3);\
	printf(" -Static:               %p, %p, %p\n", &s1, &s2, &s3);\
	printf(" -Static initialized:   %p, %p, %p\n", &si1, &si2, &si3);\
	printf(" -Automatic:            %p, %p, %p\n", &a1, &a2, &a3);\
} while(0)
	
void print_blocks(tMemoryList ml) {}

void print_pmap() {}



double var1;
double var2;
double var3;

double var4 = 2.5;
double var5 = 67.2;
double var6 = 0;

void Cmd_mem(int n, char *tr[], tMemoryList *ml) {
	static int var7;
	static int var8;
	static int var9;
	
	static int var10 = 15;
	static int var11 = 27;
	static int var12 = 42;
	
	char var13 = 'd';
	char var14 = 'a';
	char var15 = 'Z';
	
	
	if(n <= 1 || !strcmp(tr[1], "-all")) {
		print_funcs(Cmd_dir, Cmd_mem, Cmd_getdirparams, printf, scanf, strcmp);
		print_vars(var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15);
		print_blocks(*ml);
		print_pmap();
	} else for(int i = 1; i < n; i++) {
		if(!strcmp(tr[i], "-funcs"))  print_funcs(Cmd_dir, Cmd_mem, Cmd_getdirparams, printf, scanf, strcmp);
		if(!strcmp(tr[i], "-vars"))   print_vars(var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15);
		if(!strcmp(tr[i], "-blocks")) print_blocks(*ml);
		if(!strcmp(tr[i], "-pmap"))   print_pmap();
	}
	
}

#undef print_funcs
#undef print_vars