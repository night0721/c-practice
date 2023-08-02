#include <Windows.h>
#include <stdio.h>
#include <stdbool.h>

HHOOK keyboardHook;

// Keyboard hook callback function
LRESULT CALLBACK KeyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0 && wParam == WM_KEYUP) {
        // Get the virtual key code and key states
        KBDLLHOOKSTRUCT* kbStruct = (KBDLLHOOKSTRUCT*) lParam;
        int virtualKeyCode = kbStruct->vkCode;
        bool shiftPressed = (GetAsyncKeyState(VK_SHIFT) & 0x8000) != 0;
        bool ctrlPressed = (GetAsyncKeyState(VK_CONTROL) & 0x8000) != 0;
        bool laltPressed = (GetAsyncKeyState(VK_LMENU) & 0x8000) != 0;
        bool raltPressed = (GetAsyncKeyState(VK_RMENU) & 0x8000) != 0;
        bool altPressed = laltPressed || raltPressed;
        if (wParam == WM_KEYUP) {
            if (virtualKeyCode > 0x2F && virtualKeyCode < 0x5A) {
                printf("%c", (char) virtualKeyCode);
            }
			else {
				printf("Key Logged: %i\n", virtualKeyCode);
			}
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
        }
        // Check for Ctrl+C combination
        if (ctrlPressed && altPressed && virtualKeyCode == 'Q') {
            system("\"C:\\Program Files\\BraveSoftware\\Brave-Browser\\Application\\brave.exe\"");
        }
        if (ctrlPressed && virtualKeyCode == 'V') {
            printf("Also ctrl V\n");
        }
    }
    // Call the next hook in the chain
    return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
}

// Console control handler function for Ctrl+C event
BOOL WINAPI ConsoleCtrlHandler(DWORD ctrlType) {
    //if (ctrlType == CTRL_C_EVENT) {
    //    printf("Ctrl+C is intercepted via console control handler. Do not exit the process.\n");
    //    // Here you can execute your desired action when Ctrl+C is pressed.
    //    // For example, you can show a message, ignore the event, or take other actions.
    //    return TRUE; // Returning TRUE from the control handler prevents the default behavior (exit the process).
    //}

    return FALSE; // Return FALSE to let the default behavior take place for other control events.
}

int main() {
    // Set up the hook
    keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardHookProc, NULL, 0);
    if (keyboardHook == NULL) {
        printf("Failed to set up the keyboard hook.\n");
        return 1;
    }

    // Set the console control handler
    if (!SetConsoleCtrlHandler(ConsoleCtrlHandler, TRUE)) {
        printf("Failed to set console control handler.\n");
        return 1;
    }

    // Message loop to keep the application running and process the hook and control messages
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Unhook the keyboard hook
    UnhookWindowsHookEx(keyboardHook);

    return 0;
}
