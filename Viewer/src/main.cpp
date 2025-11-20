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
using namespace QMB;

// This gets called when the window closes
LRESULT on_win_close(HWND hwnd, WPARAM, LPARAM) {
	MessageBoxW(hwnd, (LPWSTR)L"Window is closing!", (LPWSTR)L"Event", MB_OK);
	PostQuitMessage(0);
	return 0;
}

// this gets called when the window gets told to update by Windows
LRESULT on_win_paint(WidgetBase* widget, WPARAM, LPARAM) { // bp here
	if (!widget) return 0;

	HWND hwnd = widget->operator HWND(); // use accessor instead of casting
	QMB::Window* window = dynamic_cast<QMB::Window*>(widget);
	if (!window || !window->img) return 0;

	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);

	RECT rc;
	GetClientRect(hwnd, &rc);
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;
	Image resized = window->img.resized(width, height); // bp

	resized.draw(ps, hdc, hwnd, 0, 0); // optimized out?


	EndPaint(hwnd, &ps);
	return 0;
}





LRESULT on_drop(WidgetBase* widget, WPARAM wParam, LPARAM lParam)
{
	HWND hwnd = (HWND)*widget;

	// get the window pointer
	QMB::Window* window = (QMB::Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
	assert(window != nullptr);

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
			window->img = std::move(QMB::Image(path));
			InvalidateRect(hwnd, NULL, TRUE);
		}
	}

	DragFinish(hDrop);
	return 0;
}


int main()
{
	Application app;
	app.init();
	Window win;
	win.init(app, (LPWSTR)L"QuickMenuBuilder v. 0.1", 100, 100, 500, 400);
	//Button button;
	//button.init(win, app, 0, 0, 200, 200);
	//SendMessage(button, WM_SETTEXT, 0, (LPARAM)L"Button");

	win.on_file_drop(on_drop);
	win.on_paint(on_win_paint);


	MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0)) { // bp
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

}