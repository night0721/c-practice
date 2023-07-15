#include <Windows.h>
#include <stdio.h>

void RegisterToRegistry(const char* appName, const char* exePath) {
    HKEY hKey;
    LPCTSTR runKey = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";

    // Open the run key in the registry
    if (RegOpenKeyEx(HKEY_CURRENT_USER, runKey, 0, KEY_QUERY_VALUE, &hKey) == ERROR_SUCCESS) {
        // Check if the application is already registered
        char valueData[MAX_PATH];
        DWORD valueSize = sizeof(valueData);
        if (RegQueryValueEx(hKey, appName, NULL, NULL, (LPBYTE) valueData, &valueSize) == ERROR_SUCCESS) {
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
        if (RegSetValueEx(hKey, appName, 0, REG_SZ, (LPBYTE) exePath, strlen(exePath) + 1) == ERROR_SUCCESS) {
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
