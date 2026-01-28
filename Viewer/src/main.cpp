#include "Backend/vgui/vgui_event_win32_impl.h"
#include "Backend/vgui/vgui_window.h"
#include "Backend/vgui/vgui_event.h"
#include "Backend/qmb/QMBApplication.h"
#include "Backend/vgui/vgui_background.h"
#include "Backend/vgui/vgui_button.h"

#include <format>
#include <memory>
using namespace native;
using namespace vgui;



int main()
{



	


	// Make an Windows application
	qmb::QMBApplication app;

	// initialize it
	app.init();

	// make a Windows window, capable of VGUI rendering (this is what took forever)
	vgui::VWindow win(&app);

	// Initialize the window
	win.init(app, (LPWSTR)L"QuickMenuBuilder v. 0.1", 100, 100, 500, 400);


	app.link_window(win);

	std::unique_ptr<Layer> layer = std::make_unique<Layer>(0);
	
	std::unique_ptr<Widget> background = std::make_unique<VBackground>(win);
	std::unique_ptr<Widget> button = std::make_unique<VButton>();


	VBackground* bg = dynamic_cast<VBackground*>(background.get());
	bg->img = qmb::Image::load_image("C:/Users/devin/Desktop/morty.jpg");

	layer->insert("bg", std::move(background));
	layer->insert("button", std::move(button));
	win.m_LayerStack.insert("layer", std::move(layer));

	app.m_Window = &win;
	win.m_Owner = static_cast<native::Application*>(&app);

	MSG msg;

	// main loop
	while (!app.status) {
		while (GetMessage(&msg, nullptr, 0, 0)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);


			//vgui::vgui_event_win32_impl(&app, evt, msg);

			//evt.free();

			if (app.status) break;

		}

	}

}