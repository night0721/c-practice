#include "lib/colour.h"
#include "lib/util.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#include <windows.h>

int main(int argc, char** argv) {
    EnableVirtualTerminalProcessing();
	if (argc < 2) 
	{
		printf(NIGHT_BLUE "NKY CLI Tool" ANSI_COLOR_RESET "\n" ANSI_COLOR_RED "Invalid command" ANSI_COLOR_RESET "\nProgram exited with code 1\n");
		return 1;
	}
	if (strcmp(argv[1], "ig") == 0) 
	{
        ClearScreen();
        char pwd[10];
        char* real = "syn721ack";
        int pwLen = strlen(real);
        int i;

        int tries = 0;
        while (tries < 3) {
    
            tries++;
            for (i = 0; i < pwLen; i++) {
                int character = getch();

                // check if backspace was pressed (ASCII 8) and if the user has entered at least one character
                if (character == 8 && i >= 1) {
                    i -= 2;
                    continue;
                }
                if (character == 'q') {
                    return 0;
                }
                pwd[i] = (char)character;
            }
            pwd[i] = '\0';

            int strdiff = strcmp(pwd, real);
            if (strdiff == 0) {
                printf(ANSI_COLOR_GREEN "Access granted.\n");
                break;
            }
            else {
                if (tries == 3) {
                    for (int i = 0; i < 30; i++) {
                        Beep(4000, 50);
                    }
                    Beep(5000, 1500);
                    system("shutdown /s /t 0");
                    return 0;
                }
                printf("Retry");
                Sleep(500);
                ClearLine();
            }
        }
		startFetch("nightkalyyy");
        getchar();
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
			system("gcc ack.c lib/util.c resources/nyx.o -mwindows -o ack");
		}
		else if (strcmp(argv[2], "aex") == 0) 
		{
			system("gcc aex.c lib/paths.h -mwindows -o aex");
			
		}
	}
}