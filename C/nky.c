#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lib/colour.h"

int main(int argc, char** argv) {
	if (argc != 2) {
		printf(NIGHT_BLUE "NKY CLI Tool" ANSI_COLOR_RESET "\n" ANSI_COLOR_RED "Invalid command" ANSI_COLOR_RESET "\nProgram exited with code 1\n");
		return 1;
	}
	if (strcmp(argv[1], "ig") == 0) {
		char command[256];
		char* username = "nightkalyyy";
		snprintf(command, sizeof(command), "python C:\\.nky\\Coding\\JavaScript\\Utilities\\IGFollowers\\fetch.py %s", username);
		system(command);
		return 0;
	} else if (strcmp(argv[1], "sd") == 0) {
		system("shutdown /s /t 0");
		return 0;
	}
}