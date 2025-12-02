#include "native/Application.h"
#include "native/Window.h"
#include "native/Button.h"
#include "native/Image.h"
#include "components/paint.h"
#include "components/ui.h"
#include <format>
using namespace native;

static inline Image g_BackgroundImg;




int main()
{
	Application app;
	app.init();
	Window win;
	win.init(app, (LPWSTR)L"QuickMenuBuilder v. 0.1", 100, 100, 500, 400);




	app.run();

}