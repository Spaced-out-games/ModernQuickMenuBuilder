#include <iostream>
#include "../Backend/Application.h"
#include "Window.h"
#include "Button.h"
#include <cassert>
#include "../Backend/Image.h"
#include <format>
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")


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

	QMB::Window* widget = (QMB::Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);


	// early exit if the custom pointer is unassigned
	if (!widget) return 0;


	RECT rc;
	GetClientRect(hwnd, &rc);
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;


	// draw the resized image to the window
	if(widget->img)
		widget->img.resized(width, height).draw(ps, hdc, hwnd, 0, 0);


	
	

	//if(widget && widget->img)
	//	widget->img.draw(ps, hdc,  hwnd, 0, 0);
	EndPaint(hwnd, &ps);
	return 0;
}


LRESULT on_button_press(HWND hwnd, WPARAM, LPARAM)
{
	

	//SetWindowLong(hwnd, GWL_EXSTYLE, 0);
	std::cout << "button pressed!\n";
	SetWindowPos(hwnd, NULL, 0, 0, 0, 0,
		SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
	return 0;
}

LRESULT on_button_release(HWND hwnd, WPARAM, LPARAM)
{

	//SetWindowLong(hwnd, GWL_EXSTYLE, 1);
	std::cout << "button released!\n";
	SetWindowPos(hwnd, NULL, 0, 0, 0, 0,
		SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
	return 0;
}

LRESULT on_drop(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	// get the window pointer
	QMB::Window* widget = (QMB::Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
	assert(widget != nullptr);

	HDROP hDrop = (HDROP)wParam;
	UINT fileCount = DragQueryFile(hDrop, 0xFFFFFFFF, nullptr, 0);

	for (UINT i = 0; i < fileCount; ++i)
	{
		char filePath[MAX_PATH];
		DragQueryFileA(hDrop, i, filePath, MAX_PATH);

		// Optionally check the extension
		std::string path(filePath);
		if (path.ends_with(".bmp") || path.ends_with(".BMP"))
		{
			std::cout << std::format("Dropped file {}", path);

			//wid

			//widget->img.free();
			widget->img = std::move(QMB::Image(path));
			InvalidateRect(hwnd, NULL, TRUE);
		}
	}

	DragFinish(hDrop);
	return 0;
}


int main()
{
	QMB::Application app;
	app.init();
	QMB::Window win;
	win.init(app, (LPWSTR)L"QuickMenuBuilder v. 0.1", 100, 100, 500, 400, on_win_close, on_win_paint, nullptr, on_drop);
	QMB::Button button;
	//button.init(win, app, 0, 0, 200, 200, on_button_press, on_button_release, nullptr);
	SendMessage(win, WM_SETTEXT, 0, (LPARAM)L"Button");

	MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

}