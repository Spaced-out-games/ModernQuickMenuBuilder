#include <iostream>
#include "../Backend/Application.h"
#include "Window.h"
#include "Button.h"


// This gets called when the window closes
LRESULT on_win_close(HWND hwnd, WPARAM, LPARAM) {
	MessageBoxW(hwnd, (LPWSTR)L"Window is closing!", (LPWSTR)L"Event", MB_OK);
	PostQuitMessage(0);
	return 0;
}

// this gets called when the window gets told to update by Windows
LRESULT on_win_paint(HWND hwnd, WPARAM, LPARAM) {
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);
	//TextOutW(hdc, 20, 20, (LPWSTR)L"Hello Window!", 13);
	EndPaint(hwnd, &ps);
	return 0;
}


LRESULT on_button_press(HWND hwnd, WPARAM, LPARAM)
{
	std::cout << "button pressed!\n";
	return 0;
}

LRESULT on_button_release(HWND hwnd, WPARAM, LPARAM)
{
	std::cout << "button released!\n";
	return 0;
}


int main()
{
	QMB::Application app;
	app.init();
	QMB::Window win;
	win.init(app, (LPWSTR)L"QuickMenuBuilder v. 0.1", 100, 100, 500, 400, on_win_close, on_win_paint);
	QMB::Button button;
	button.init(win, app, 0, 0, 200, 200, on_button_press, on_button_release, nullptr);
	
	MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

}