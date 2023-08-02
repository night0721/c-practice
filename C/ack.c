#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <wchar.h>
#include "util.h"

HWND hwndGUI;  // Separate window handle for GUI window

LRESULT CALLBACK GuiWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    //printf("Message received: %d\n", message);
    switch (message) { 
        case WM_COMMAND:
            if (LOWORD(wParam) == 1) {
                MessageBox(hWnd, "Getting data!", "Message", MB_OKCANCEL);
                HWND hTextBox = GetDlgItem(hWnd, 2);
                // Get the length of the text in the text box
                int length = GetWindowTextLength(hTextBox);
                // Allocate a buffer to store the text
                char* buffer = (char*) malloc(length + 1);
                if (length != 0) {
                    GetWindowText(hTextBox, buffer, length + 1);
                } else {
                    buffer = (char*) malloc(12);
                    if (buffer == NULL) {
						printf("Error allocating memory!\n");
						exit(1);
					}
                    strcpy(buffer, "nightkalyyy");
                }
                char command[256];
                snprintf(command, sizeof(command), "python C:\\.nky\\Coding\\JavaScript\\Utilities\\IGFollowers\\fetch.py %s", buffer);
                system(command);
                free(buffer);
            }
            else if (LOWORD(wParam) == 3) {
                HWND hTextBox = GetDlgItem(hWnd, 2);
                // Get the length of the text in the text box
                int length = GetWindowTextLength(hTextBox);
                // Allocate a buffer to store the text
                char* buffer = (char*) malloc(length + 1);
                if (buffer) {
                    // Get the text from the text box and store it in the buffer
                    GetWindowText(hTextBox, buffer, length + 1);

                    // Display the text in a message box (you can process the text as needed)
                    MessageBox(hWnd, buffer, "Text Box Content", MB_OK);

                    // Free the allocated buffer
                    free(buffer);
                }
            }
            break;
        case WM_CLOSE:
            ShowWindow(hWnd, SW_HIDE);
            exit(1);
            break;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

void CreateGUIElements(HWND hwnd, HINSTANCE hInstance) {
    // Create a button
    CreateWindow(
        "BUTTON",           // Predefined class
        "Get Instagram Followers",         // Button text
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
        10, 10, 500, 30,    // Position and size
        hwnd,               // Parent window
        (HMENU) 1,           // Button identifier
        hInstance,          // Instance handle
        NULL                // No additional data
    );

    CreateWindow(
        "BUTTON",
        "Get text from text box",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        500, 10, 200, 30,
        hwnd,
        (HMENU)3,
        hInstance,
        NULL
    );

    // Create a text box
    CreateWindow(
        "EDIT",             // Predefined class
        "",                 // Text box text
        WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL,  // Styles
        10, 50, 200, 100,   // Position and size
        hwnd,               // Parent window
        (HMENU) 2,               // No menu
        hInstance,          // Instance handle
        NULL                // No additional data
    );
}


void GuiThread() {
    HINSTANCE hInstance = GetModuleHandle(NULL);

    const char* CLASS_NAME = "AckClass";

    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = GuiWindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hIcon = LoadIcon(hInstance, "MYICON");

    RegisterClass(&wc);

    // Create the window
    hwndGUI = CreateWindowEx(
        WS_EX_ACCEPTFILES,                  // Optional window styles
        CLASS_NAME,                         // Window class
        "Ack",                              // Window text
        WS_OVERLAPPEDWINDOW,                // Window style
        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL,       // Parent window
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
    );

    if (hwndGUI == NULL)
        return;

    CreateGUIElements(hwndGUI, hInstance);

    // Display the window
    ShowWindow(hwndGUI, SW_SHOWNORMAL);

    // Message loop for your GUI application
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}


int main() {
    EnableVirtualTerminalProcessing();
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH); // Get the path of the executable currently running
    RegisterAppToRegistry("Ack", buffer);
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
            printf("Access granted.\n");
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
    GuiThread();
}
