/*
* Basic functions for C
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Windows.h>

#define WINDOWS 1

bool isWindowsTerminal(void) {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hOut == INVALID_HANDLE_VALUE) {
		return false;
	}

	DWORD dwMode;
	if (!GetConsoleMode(hOut, &dwMode)) {
		return false;
	}

	// Check if ENABLE_VIRTUAL_TERMINAL_PROCESSING flag is set
	return (dwMode & ENABLE_VIRTUAL_TERMINAL_PROCESSING) != 0;
}

void ClearScreen(void) {
	if (isWindowsTerminal()) {
		fprintf(stdout, "\033[2J"); // clean screen
		fprintf(stdout, "\033[1;1H"); // move cursor to the first line
	}
	else {
		#ifdef WINDOWS
				system("cls");
		#endif
		#ifdef LINUX
				system("clear");
		#endif
	}
}

void ClearLine(void) {
	fputs("\033[A\033[2K", stdout); // Move cursor up one line and clear line
	printf("\r");
}

bool EnableVirtualTerminalProcessing(void) {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hOut == INVALID_HANDLE_VALUE) {
		return false;
	}

	DWORD dwMode;
	if (!GetConsoleMode(hOut, &dwMode)) {
	    return false;
	}

	// Enable the ENABLE_VIRTUAL_TERMINAL_PROCESSING flag
	if (!SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING)) {
	    return false;
	}

	return true;
}