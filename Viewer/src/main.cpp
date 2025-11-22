#include "Windows/Application.h"
#include "Windows/Window.h"
#include "Windows/Button.h"
#include "Windows/Image.h"
#include "components/paint.h"
#include "components/ui.h"
#include <format>
using namespace Windows;

static inline Image g_BackgroundImg;




int main()
{
	Application app;
	app.init();
	Window win;
	win.init(app, (LPWSTR)L"QuickMenuBuilder v. 0.1", 100, 100, 500, 400);

	Button button;
	button.init(win, app, 0, 0, 30, 30);

	button.on_resize([](WidgetBase* widget, WPARAM wParam, LPARAM lParam) -> LRESULT {
		widget->hide();
		return 0;
	});


	win.on_file_drop([](WidgetBase* widget, WPARAM wParam, LPARAM lParam) -> LRESULT {
		return ui::drag_drop_bg_img(*widget, g_BackgroundImg, wParam, lParam);
	});



	win.on_paint([](WidgetBase* widget, WPARAM wParam, LPARAM lParam) -> LRESULT {
		PAINTSTRUCT ps;
		HDC hdc;
		widget->begin_paint(ps, hdc);
		LRESULT result = paint::render_background_image(*widget, hdc, g_BackgroundImg);
		widget->end_paint(ps);
		return result;
	});

	win.on_resize([](WidgetBase* widget, WPARAM wParam, LPARAM lParam) -> LRESULT {
		PAINTSTRUCT ps;
	widget->invalidate();
	return 0;
	});


	app.run();

}