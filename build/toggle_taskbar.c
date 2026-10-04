#define UNICODE
#define _WIN32_WINNT 0x0600

#include "toggle_taskbar.h"
#include <windows.h>

void ToggleTaskbar(void) {
  HWND taskbar = FindWindowW(L"Shell_TrayWnd", NULL);
  if (!taskbar)
    return;

  APPBARDATA abd = {0};
  abd.cbSize = sizeof(APPBARDATA);
  abd.hWnd = taskbar;

  // Get current state
  UINT state = (UINT)SHAppBarMessage(ABM_GETSTATE, &abd);

  // Toggle autohide
  if (state & ABS_AUTOHIDE) {
    abd.lParam = 0;
  } else {
    abd.lParam = ABS_AUTOHIDE;
  }

  SHAppBarMessage(ABM_SETSTATE, &abd);

  // Broadcast to all windows so they know the taskbar moved
  PostMessageW(HWND_BROADCAST, WM_SETTINGCHANGE, 0, (LPARAM)L"TraySettings");
}
