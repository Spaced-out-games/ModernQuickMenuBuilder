#include "Backend/native/Application.h"
#include "Backend/native/Window.h"
#include "Backend/native/Button.h"
#include "Backend/native/Image.h"
#include "Backend/vgui/vgui_window.h"
#include "Backend/vgui/vgui_context.h"
#include "Backend/vgui/vgui_widget.h"
#include "Backend/vgui/vgui_button.h"
#include "Backend/vgui/vgui_background.h"
#include "Backend/vgui/vgui_page.h"

#include "Backend/components/paint.h"
#include "Backend/components/ui.h"
#include "Backend/components/load.h"
#include "thirdparty/json/json.hpp"

#include <format>
#include <memory>
using namespace native;
using namespace vgui;

static inline Image g_BackgroundImg;




int main()
{
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


	// Take a guess
	win.enable_drag_drop();

	// Includes the background and a virtual button later on
	vgui::Page   vgui_test_page;
	vgui_context.SetActivePage(vgui_test_page);






	// -------------------- set up background image-------------------- //


	std::unique_ptr<vgui::VBackground> background = std::make_unique<vgui::VBackground>();

	background->img = qmb::Image::load_image("../src/Main.bmp");




	// ------------------------ set up a buttion ------------------------ //


	std::unique_ptr<vgui::VButton> button = std::make_unique<vgui::VButton>();

	button->bindAction(ActionType::EXIT, "Exitting...");


	// ------------------------------------------------------------------ //


	// todo: template scene::insert(), scene::get(). Nice ergonomics

	vgui_test_page.insert(std::move(background));
	vgui_test_page.insert(std::move(button));




	json config = qmb::load_jsonc("../src/main.jsonc");

	if (!config.empty())
	{

	}


	win.ToggleFullscreen();
	win.redraw_now();

	// triggers a resize event to trigger a redraw


	// main loop
	app.run();

}