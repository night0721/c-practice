#include <windows.h>

#define ID_BUTTON_START_AEX 1001

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
  switch (msg) {
  case WM_CREATE: {
    // Create the button
    HWND hButtonStartAEX = CreateWindow(
        "BUTTON", "Start AEX", WS_VISIBLE | WS_CHILD | BS_OWNERDRAW, 50, 50,
        100, 30, hwnd, (HMENU)ID_BUTTON_START_AEX, NULL, NULL);

    break;
  }
  case WM_COMMAND: {
    if (LOWORD(wParam) == ID_BUTTON_START_AEX) {
      // Handle button click event here
      MessageBox(hwnd, "Start AEX button clicked!", "Button Clicked",
                 MB_OK | MB_ICONINFORMATION);
    }
    break;
  }
  case WM_DRAWITEM: {
    LPDRAWITEMSTRUCT pDIS = (LPDRAWITEMSTRUCT)lParam;
    if (pDIS->CtlID == ID_BUTTON_START_AEX) {
      // Draw the custom button
      HDC hdc = pDIS->hDC;
      RECT rc = pDIS->rcItem;

      // Fill the background with green color
      HBRUSH hBrush = CreateSolidBrush(RGB(0, 255, 0));
      FillRect(hdc, &rc, hBrush);

      // Set the text color to red
      SetTextColor(hdc, RGB(255, 0, 0));

      // Draw the button text
      char buttonText[32];
      GetWindowText(pDIS->hwndItem, buttonText, sizeof(buttonText));
      DrawText(hdc, buttonText, -1, &rc,
               DT_CENTER | DT_SINGLELINE | DT_VCENTER);

      DeleteObject(hBrush);
    }
    break;
  }
  case WM_DESTROY: {
    PostQuitMessage(0);
    break;
  }
  default: {
    return DefWindowProc(hwnd, msg, wParam, lParam);
  }
  }
  return 0;
}

int main() {
  // Register the window class
  const char *CLASS_NAME = "MyWindowClass";
  WNDCLASS wc = {0};
  wc.lpfnWndProc = WndProc;
  wc.hInstance = GetModuleHandle(NULL);
  wc.lpszClassName = CLASS_NAME;

  RegisterClass(&wc);

  // Create the window
  HWND hwnd = CreateWindow(CLASS_NAME, "Colored Button Example",
                           WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                           300, 200, NULL, NULL, GetModuleHandle(NULL), NULL);

  if (hwnd == NULL)
    return 0;

  // Show the window
  ShowWindow(hwnd, SW_SHOWDEFAULT);

  // Run the message loop
  MSG msg = {0};
  while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return 0;
}
