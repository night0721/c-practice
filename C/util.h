#ifndef UTIL_H
#define UTIL_H

#include <stdbool.h>

void ClearScreen(void);

void ClearLine(void);

bool isWindowsTerminal(void);

bool EnableVirtualTerminalProcessing(void);

#endif