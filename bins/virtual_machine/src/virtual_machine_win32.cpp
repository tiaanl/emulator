#define WIN32_LEAN_AND_MEAN
#include <windows.h>

constexpr const char* g_main_window_class_name = "emulator_virtual_machine_main_window";

LRESULT CALLBACK main_window_proc(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam) {
switch (msg) {
case WM_DESTROY: {
PostQuitMessage(0);
break;
}

case WM_PAINT: {
PAINTSTRUCT ps = {};
BeginPaint(wnd, &ps);

HFONT font, old_font;

font = (HFONT)GetStockObject(ANSI_FIXED_FONT);
if (old_font = (HFONT)SelectObject(ps.hdc, font); old_font) {
DrawTextA(ps.hdc, "Emulator", 8, &ps.rcPaint, 0);

SelectObject(ps.hdc, old_font);
}

EndPaint(wnd, &ps);
break;
}
}

return DefWindowProcA(wnd, msg, wparam, lparam);
}

int main() {
  HINSTANCE instance = GetModuleHandleA(nullptr);

  WNDCLASSEXA wc = {sizeof(WNDCLASSEXA),
                    CS_HREDRAW | CS_VREDRAW,
                    main_window_proc,
                    0,
                    0,
                    instance,
                    LoadIconA(nullptr, IDI_APPLICATION),
                    LoadCursorA(nullptr, IDC_ARROW),
                    (HBRUSH)(COLOR_WINDOW + 1),
                    nullptr,
                    g_main_window_class_name,
                    LoadIconA(nullptr, IDI_APPLICATION)};

  RegisterClassExA(&wc);

  HWND handle = CreateWindowExA(WS_EX_APPWINDOW, g_main_window_class_name, "Emulator",
                                WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                                CW_USEDEFAULT, HWND_DESKTOP, nullptr, instance, nullptr);

  ShowWindow(handle, SW_SHOW);

  MSG msg;
  while (GetMessageA(&msg, nullptr, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessageA(&msg);
  }

  return 0;
}
