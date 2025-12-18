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
	layer.insert("generic", std::move(std::make_unique<Widget>(0, 0, 20, 20)));
	layer.insert("background", std::move(std::make_unique<VBackground>()));
	layer.insert("button", std::move(std::make_unique<VButton>(Action_t::OPEN_FILE, "")));


	std::cout << "generic hash: " << hash("generic") << "\n";
	std::cout << "background hash: " << hash("background") << "\n";
	std::cout << "\"\" hash: " << hash("") << "\n";
	std::cout << "bad-widget hash: " << hash("bad-widget") << "\n";

	std::cout << layer.size();
	layer.getWidgetById("background")->w = 2000;
	assert(layer.getWidgetById("generic")->w == 20);
	auto* bg = dynamic_cast<VBackground*> (layer.getWidgetById("background"));


	size_t size = layer.size();

	// remove the background
	layer.remove("background");

	auto* bg_removed = dynamic_cast<VBackground*> (layer.getWidgetById("background"));
	assert(bg_removed == nullptr && layer.logical_size() == 2 && layer.size() == size);
	auto* button = layer.getWidgetById("button");

	assert(dynamic_cast<VButton*>(button) != nullptr && button == layer.m_Widgets[2].m_Widget.get());


	assert(layer.m_Widgets[1].m_Widget == nullptr);
	assert(layer.pTail == 2 && layer.pHead == 0);

	assert(layer.m_Widgets[layer.pHead].m_Next == layer.pTail);

	layer.insert("background", std::move(std::make_unique<VBackground>()));

	assert(layer.pTail == 1 && layer.pHead == 0);
	
	layer.remove("button");
	layer.insert("new-thing", std::move(std::make_unique<Widget>(0, 0, 20, 20)));

	// try deleting things that don't exist
	layer.remove("");
	// try adding bad widgets
	layer.insert("bad-widget", nullptr);

	assert(layer.getWidgetById("bad-widget") == nullptr);

}