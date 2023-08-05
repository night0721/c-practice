#ifndef UTIL_H
#define UTIL_H

#include <stdbool.h>

int random(int min, int max);

void ClearScreen(void);

void ClearLine(void);

bool isWindowsTerminal(void);

bool EnableVirtualTerminalProcessing(void);

void RegisterAppToRegistry(const char* appname, const char* exepath);

void startFetch(char* username);

#endif