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
#include "Backend/overrides/paint.h"
#include "Backend/overrides/ui.h"
#include "Backend/vgui/vgui_build.h"
#include "thirdparty/json/json.hpp"

#include <format>
#include <memory>
using namespace native;
using namespace vgui;

static inline Image g_BackgroundImg;




int main()
{

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
	
	// Make a book
	std::unique_ptr<Book> book = std::make_unique<Book>();

	// load json


	


	




	// Create main menu page
	//auto main_menu = std::make_unique<Page>();


	json file = vgui::load_jsonc(sample_widget_path);

	if (file["settings"]["fullscreen"].get<bool>())
	{
		win.ToggleFullscreen();
	}


	auto main_menu = vgui::load_page(file["widgets"]);







	


	// Add the page to the book
	book->insert({ "main-menu", std::move(main_menu) });


	// Tell context to use the book
	vgui_context.SetBook(std::move(book));
	vgui_context.LoadPage("main-menu");
	



	win.redraw_now();



	// main loop
	app.run();

}