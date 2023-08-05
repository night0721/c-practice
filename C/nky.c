#include "lib/colour.h"
#include "lib/util.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv) {
	if (argc < 2) 
	{
		printf(NIGHT_BLUE "NKY CLI Tool" ANSI_COLOR_RESET "\n" ANSI_COLOR_RED "Invalid command" ANSI_COLOR_RESET "\nProgram exited with code 1\n");
		return 1;
	}
	if (strcmp(argv[1], "ig") == 0) 
	{
		startFetch("nightkalyyy");
		return 0;
	} else if (strcmp(argv[1], "sd") == 0) 
	{
		system("shutdown /s /t 0");
		return 0;
	}
	else if (strcmp(argv[1], "gcc") == 0) 
	{
		chdir("C:\\.nky\\Coding\\C\\C\\C");
		if (strcmp(argv[2], "ins") == 0 || strcmp(argv[2], "ig") == 0) 
		{
			system("gcc ins.c lib/json/json.c -lm -o ins");
		} 
		else if (strcmp(argv[2], "ack") == 0) 
		{
			system("gcc ack.c lib/util.c lib/paths.h nyx.o -lgdi32 -mconsole -o ack");
		}
		else if (strcmp(argv[2], "aex") == 0) 
		{
			system("gcc aex.c lib/paths.h -mwindows -o aex");
			
		}
	}
}