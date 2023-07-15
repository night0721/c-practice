#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <wchar.h>
#include "util.h"
#include "registry.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg)
    {
    case WM_COMMAND:
        // Handle button click event
        if (LOWORD(wParam) == 1)
        {
            MessageBox(hwnd, "Hello World!", "Message", MB_OKCANCEL);
        }
        break;

    case WM_DESTROY:
        // Quit the application when the window is closed
        PostQuitMessage(0);
        break;
    }

    // Call the default window procedure for other messages
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH); // Get the path of the executable currently running
    RegisterToRegistry("Ack", buffer);
	char pwd[10];
	char *real = "syn721ack";
	int pwLen = strlen(real);
	int i;
	clrscr();
	int tries = 0;
	while (tries < 3) {
		tries++;
		for (i = 0; i < pwLen; i++) {
			pwd[i] = getch();
			if (pwd[i] == 'q') {
				return 0;
			}
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
			for (i = 0; i < pwLen; i++) {
				pwd[i] = '\0';
			}
		}
	}
    const char* CLASS_NAME = "MyWindowClass";

    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    //wc.hIcon = LoadIcon(hInstance, IDI_APPLICATION);

    RegisterClass(&wc);

    // Create the window
    HWND hwnd = CreateWindowEx(
        0,                                  // Optional window styles
        CLASS_NAME,                         // Window class
        "Ack",                        // Window text
        WS_OVERLAPPEDWINDOW,                // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,       // Parent window
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
    );

    if (hwnd == NULL)
        return 0;

    // Create a button
    CreateWindow(
        "BUTTON",           // Predefined class
        "Click me",         // Button text
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
        10, 10, 100, 30,    // Position and size
        hwnd,               // Parent window
        (HMENU)1,           // Button identifier
        hInstance,          // Instance handle
        NULL                // No additional data
    );

    // Create a text box
    CreateWindow(
        "EDIT",             // Predefined class
        "",                 // Text box text
        WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL,  // Styles
        10, 50, 200, 100,   // Position and size
        hwnd,               // Parent window
        NULL,               // No menu
        hInstance,          // Instance handle
        NULL                // No additional data
    );

    // Display the window
    ShowWindow(hwnd, nCmdShow);

    // Message loop
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

}
