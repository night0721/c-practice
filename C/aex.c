#include "lib/paths.h"

#include <windows.h>
#include <stdio.h>
#include <stdbool.h>

HHOOK keyboardHook;

// Keyboard hook callback function
LRESULT CALLBACK KeyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0 && wParam == WM_KEYUP) {
        KBDLLHOOKSTRUCT* kbStruct = (KBDLLHOOKSTRUCT*) lParam;
        int virtualKeyCode = kbStruct->vkCode;
        bool shiftPressed = (GetAsyncKeyState(VK_SHIFT) & 0x8000) != 0;
        bool ctrlPressed = (GetAsyncKeyState(VK_CONTROL) & 0x8000) != 0;
        bool laltPressed = (GetAsyncKeyState(VK_LMENU) & 0x8000) != 0;
        bool raltPressed = (GetAsyncKeyState(VK_RMENU) & 0x8000) != 0;
        bool altPressed = laltPressed || raltPressed;
        /*
        if (virtualKeyCode > 0x2F && virtualKeyCode < 0x5A) {
            printf("%c", (char) virtualKeyCode);
        }
		else {
			printf("Key Logged: %i\n", virtualKeyCode);
		}
        
        if (virtualKeyCode == 0x20) {
			printf(" ");
		}
        if (virtualKeyCode == 0xA0 || virtualKeyCode == 0xA1) {
            printf("Shift pressed\n");
        }
        if (virtualKeyCode == 0xA2 || virtualKeyCode == 0xA3) {
            printf("Ctrl pressed\n");
        }
        if (altPressed) {
            printf("Alt pressed\n");
        }*/

        if (ctrlPressed && altPressed && virtualKeyCode == 'Q') {
            system("\"" BRAVE_PATH "\"");
        }
        if (ctrlPressed && altPressed && virtualKeyCode == 'W') {
            system("\"" DISCORD_PATH "\"");
        }
        if (ctrlPressed && altPressed && virtualKeyCode == 'A') {
			system("wt");
		}
    }
    return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
}

int main() {
    keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardHookProc, NULL, 0);
    if (keyboardHook == NULL) {
        printf("Failed to set up the keyboard hook.\n");
        return 1;
    }

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Unhook the keyboard hook
    UnhookWindowsHookEx(keyboardHook);

    return 0;
}
