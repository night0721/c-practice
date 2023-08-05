/*
* Basic functions for C
*/

#include "paths.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

#define WINDOWS 1

// must call srand(time(NULL)) before calling this function
int random(int min, int max) {
	return (rand() % (max - min + 1)) + min;
}

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

void RegisterAppToRegistry(const char* appName, const char* exePath) {
	HKEY hKey;
	LPCTSTR runKey = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";

	// Open the run key in the registry
	if (RegOpenKeyEx(HKEY_CURRENT_USER, runKey, 0, KEY_QUERY_VALUE, &hKey) == ERROR_SUCCESS) {
		// Check if the application is already registered
		char valueData[MAX_PATH];
		DWORD valueSize = sizeof(valueData);
		if (RegQueryValueEx(hKey, appName, NULL, NULL, (LPBYTE)valueData, &valueSize) == ERROR_SUCCESS) {
			if (strcmp(valueData, exePath) == 0) {
				printf("Application is already registered.\n");
				RegCloseKey(hKey);
				return;
			}
		}
		// Close the registry key
		RegCloseKey(hKey);
	}

	// Open the run key in the registry with write access
	if (RegOpenKeyEx(HKEY_CURRENT_USER, runKey, 0, KEY_SET_VALUE, &hKey) == ERROR_SUCCESS) {
		// Add the application to the startup list
		if (RegSetValueEx(hKey, appName, 0, REG_SZ, (LPBYTE)exePath, strlen(exePath) + 1) == ERROR_SUCCESS) {
			printf("Application registered successfully!\n");
		}
		else {
			printf("Failed to register the application.\n");
		}
		// Close the registry key
		RegCloseKey(hKey);
	}
	else {
		printf("Failed to open the registry key.\n");
	}
}

void startFetch(char* username) {
	const char* pythonPath = PY_PATH;
	const char* scriptPath = INS_PY_PATH;
	const char* argument = username;

	// Construct the command line
	char commandLine[1024];
	snprintf(commandLine, sizeof(commandLine), "\"%s\" \"%s\" %s", pythonPath, scriptPath, argument);

	// CreateProcess parameters
	STARTUPINFO startupInfo;
	PROCESS_INFORMATION processInfo;
	ZeroMemory(&startupInfo, sizeof(startupInfo));
	ZeroMemory(&processInfo, sizeof(processInfo));
	startupInfo.cb = sizeof(startupInfo);

	// Create the process
	if (CreateProcess(NULL,   // ApplicationName, use NULL to use the command line
		commandLine,   // Command line
		NULL,   // Process security attributes
		NULL,   // Thread security attributes
		FALSE,  // Inherit handles from parent process
		0,      // Creation flags
		NULL,   // Use parent's environment variables
		NULL,   // Use parent's current directory
		&startupInfo,
		&processInfo)) {

		// Close process and thread handles
		CloseHandle(processInfo.hProcess);
		CloseHandle(processInfo.hThread);
	}
	else {
		// Failed to create the process.
		printf("Error starting process. Error code: %d\n", GetLastError());
		return;
	}
}