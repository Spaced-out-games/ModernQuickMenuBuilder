#include "Backend/native/Application.h"
#include "Backend/native/Window.h"
#include "Backend/native/Button.h"
#include "Backend/native/Image.h"
#include "Backend/vgui/vgui_window.h"
#include "Backend/vgui/vgui_context.h"
#include "Backend/vgui/vgui_widget.h"
#include "Backend/vgui/vgui_button.h"
#include "Backend/vgui/vgui_background.h"
#include "Backend/overrides/paint.h"
#include "Backend/overrides/ui.h"
#include "thirdparty/json/json.hpp"
#include "Backend/vgui/vgui_layer.h"

#include <format>
#include <memory>
using namespace native;
using namespace vgui;

static inline Image g_BackgroundImg;




int main()
{
	/*
	const std::string sample_widget_path = "C:/Users/devin/Documents/Visual Studio 2022/Projects/ModernQuickMenuBuilder/resources/widget.jsonc";


	


	// Make an Windows application
	Application app;

	// initialize it
	app.init();
	// make a ui context
	vgui::Context vgui_context;

	// make a Windows window, capable of VGUI rendering (this is what took forever)
	vgui::VWindow win(&vgui_context);

	// Initialize the window
	win.init(app, (LPWSTR)L"QuickMenuBuilder v. 0.1", 100, 100, 500, 400);
	
	win.redraw_now();



	// main loop
	app.run();
	*/

	
	Layer layer;

	layer.insert("generic", std::make_unique<Widget>(0, 0, 20, 20));
	layer.insert("background", std::make_unique<VBackground>());
	layer.insert("button", std::make_unique<VButton>(Action_t::OPEN_FILE, ""));

	for (Widget& widget : layer) {
		std::cout << typeid(widget).name() << "\n";  // prints dynamic type if Widget has at least one virtual function
	}
	std::cout << '\n';

	

}