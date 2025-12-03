#include "native/Application.h"
#include "native/Window.h"
#include "native/Button.h"
#include "native/Image.h"
#include "vgui/vgui_window.h"
#include "vgui/vgui_context.h"
#include "vgui/vgui_widget.h"
#include "vgui/vgui_button.h"
#include "vgui/vgui_background.h"
#include "vgui/vgui_scene.h"

#include "components/paint.h"
#include "components/ui.h"
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
	vgui::Scene   vgui_test_scene;
	vgui_context.SetActiveScene(vgui_test_scene);






	// -------------------- set up background image-------------------- //


	std::unique_ptr<vgui::VBackground> background = std::make_unique<vgui::VBackground>();

	background->img = qmb::Image::load_image("../resources/morty.jpg");




	// ------------------------ set up a buttion ------------------------ //


	std::unique_ptr<vgui::VButton> button = std::make_unique<vgui::VButton>();

	button->bindAction(Action_t::EXIT, "Exitting...");


	// ------------------------------------------------------------------ //


	// todo: template scene::insert(), scene::get(). Nice ergonomics
	
	vgui_test_scene.insert(std::move(background));
	vgui_test_scene.insert(std::move(button));

	win.ToggleFullscreen();
	win.redraw_now();

	// triggers a resize event to trigger a redraw
	//win.resize(720, 720); 


	// main loop
	app.run();

}