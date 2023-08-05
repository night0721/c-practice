#include "lib/util.h"
#include "lib/paths.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <tlhelp32.h>

HWND hwndGUI;  // Separate window handle for GUI window
HBRUSH hBrushBtn = NULL;
HBRUSH hBrushBackground = NULL;

LRESULT CALLBACK GuiWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    //printf("Message received: %d\n", message);
    switch (message) {
        case WM_ERASEBKGND: {
            HDC hdc = (HDC)wParam;

            // Set the background color of the window
            HBRUSH hBrushBackground = CreateSolidBrush(RGB(171, 132, 255));
            RECT rc;
            GetClientRect(hWnd, &rc);
            FillRect(hdc, &rc, hBrushBackground);
            DeleteObject(hBrushBackground);

            return TRUE;
        } 
    
        case WM_COMMAND:
            if (LOWORD(wParam) == 1) 
            {
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
                startFetch(buffer);
                free(buffer);
            }
            else if (LOWORD(wParam) == 3) 
            {
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
            else if (LOWORD(wParam) == 4)
            {
                const char* path = AEX_PATH;

                // CreateProcess parameters
                STARTUPINFO startupInfo;
                PROCESS_INFORMATION processInfo;
                ZeroMemory(&startupInfo, sizeof(startupInfo));
                ZeroMemory(&processInfo, sizeof(processInfo));
                startupInfo.cb = sizeof(startupInfo);

                // Create the process
                if (CreateProcess(NULL,   // ApplicationName, use NULL to use the command line
                    (LPSTR) path,   // Command line (typecast to LPSTR)
                    NULL,   // Process security attributes
                    NULL,   // Thread security attributes
                    FALSE,  // Inherit handles from parent process
                    0,      // Creation flags
                    NULL,   // Use parent's environment variables
                    NULL,   // Use parent's current directory
                    &startupInfo,
                    &processInfo)) {

                    // Successfully started the process.
                    // Wait for the process to complete (optional).
                    //WaitForSingleObject(processInfo.hProcess, INFINITE);

                    // Close process and thread handles
                    CloseHandle(processInfo.hProcess);
                    CloseHandle(processInfo.hThread);

                }
                else {
                    // Failed to create the process.
                    printf("Error starting process. Error code: %d\n", GetLastError());
                    return 1;
                }
            }
            else if (LOWORD(wParam) == 5)
            {
                // Step 1: Replace "process_name" with the name of the process you want to kill.
                const char* process_name = "aex.exe";

                HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
                PROCESSENTRY32 processEntry;
                processEntry.dwSize = sizeof(PROCESSENTRY32);

                if (Process32First(snapshot, &processEntry)) {
                    do {
                        // Step 2: Compare process names to find the desired process.
                        if (strcmp(processEntry.szExeFile, process_name) == 0) {
                            // Step 3: Use OpenProcess and TerminateProcess to kill the process.
                            HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, processEntry.th32ProcessID);
                            char showMessage[256];
                            if (hProcess != NULL) {
                                TerminateProcess(hProcess, 0);
                                CloseHandle(hProcess);
                                char showMessage[256];
                                snprintf(showMessage, sizeof(showMessage), "Process with PID %d killed successfully.", processEntry.th32ProcessID);
                                MessageBox(hWnd, showMessage, "Message", MB_OKCANCEL);
                                printf(showMessage);
                            }
                            else {
                                snprintf(showMessage, sizeof(showMessage), "Failed to kill process with PID %d.", processEntry.th32ProcessID);
                                printf(showMessage);
                            }
                            break;
                        }
                    } while (Process32Next(snapshot, &processEntry));
                }
                CloseHandle(snapshot);
            }
            break;
        case WM_CLOSE:
            ShowWindow(hWnd, SW_HIDE);
            exit(1);
            break;
        case WM_DESTROY: {
            PostQuitMessage(0);
            break;
        }
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

void CreateGUIElements(HWND hwnd, HINSTANCE hInstance) {
    // Create a button
    CreateWindow(
        "BUTTON",           // Predefined class
        "Get Instagram Followers",         // Button text
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
        150, 10, 200, 50,    // Position and size
        hwnd,               // Parent window
        (HMENU) 1,           // Button identifier
        hInstance,          // Instance handle
        NULL                // No additional data
    );

    CreateWindow(
        "BUTTON",
        "Get text from text box",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        350, 10, 200, 50,
        hwnd,
        (HMENU) 3,
        hInstance,
        NULL
    );
    CreateWindow(
        "BUTTON",
        "Start AEX",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        550, 10, 200, 50,
        hwnd,
        (HMENU)4,
        hInstance,
        NULL
    );
    CreateWindow(
        "BUTTON",
        "Kill AEX",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        750, 10, 200, 50,
        hwnd,
        (HMENU) 5,
        hInstance,
        NULL
    );

    // Create a text box
    CreateWindow(
        "EDIT",             // Predefined class
        "",                 // Text box text
        WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL,  // Styles
        350, 60, 400, 100,   // Position and size
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