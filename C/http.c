#include <Windows.h>
#include <Winhttp.h>
#include <stdio.h>

#pragma comment(lib, "Winhttp.lib")

    int main() {
    HINTERNET hSession = NULL, hConnect = NULL, hRequest = NULL;

    // Initialize WinHTTP session
    hSession = WinHttpOpen(L"WinHTTP Example/1.0", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
    if (!hSession) {
        printf("Error: WinHttpOpen failed (%d)\n", GetLastError());
        return 1;
    }

    // Set the redirect policy to automatically follow redirects
    DWORD redirectPolicy = WINHTTP_OPTION_REDIRECT_POLICY_ALWAYS;
    if (!WinHttpSetOption(hSession, WINHTTP_OPTION_REDIRECT_POLICY, &redirectPolicy, sizeof(redirectPolicy))) {
        printf("Error: WinHttpSetOption failed (%d)\n", GetLastError());
        WinHttpCloseHandle(hSession);
        return 1;
    }

    // Connect to the server
    hConnect = WinHttpConnect(hSession, L"api.night0721.me", INTERNET_DEFAULT_HTTP_PORT, 0);
    if (!hConnect) {
        printf("Error: WinHttpConnect failed (%d)\n", GetLastError());
        WinHttpCloseHandle(hSession);
        return 1;
    }

    // Create an HTTP request handle
    hRequest = WinHttpOpenRequest(hConnect, L"GET", L"/api/v1/fun/reverse?text=Hellllloooo", NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, 0);
    if (!hRequest) {
        printf("Error: WinHttpOpenRequest failed (%d)\n", GetLastError());
        WinHttpCloseHandle(hConnect);
        WinHttpCloseHandle(hSession);
        return 1;
    }

    // Send the request
    if (!WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0)) {
        printf("Error: WinHttpSendRequest failed (%d)\n", GetLastError());
        WinHttpCloseHandle(hRequest);
        WinHttpCloseHandle(hConnect);
        WinHttpCloseHandle(hSession);
        return 1;
    }

    // Wait for the response
    if (!WinHttpReceiveResponse(hRequest, NULL)) {
        printf("Error: WinHttpReceiveResponse failed (%d)\n", GetLastError());
        WinHttpCloseHandle(hRequest);
        WinHttpCloseHandle(hConnect);
        WinHttpCloseHandle(hSession);
        return 1;
    }

    // Read the response
    DWORD bytesRead;
    BYTE buffer[1024];
    while (WinHttpReadData(hRequest, buffer, sizeof(buffer), &bytesRead) && bytesRead > 0) {
        // Process or save the data as needed
        // Here, we'll just print it to the console
        fwrite(buffer, 1, bytesRead, stdout);
    }

    // Close the handles
    WinHttpCloseHandle(hRequest);
    WinHttpCloseHandle(hConnect);
    WinHttpCloseHandle(hSession);

    return 0;
}

