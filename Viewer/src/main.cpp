/*
// Test driver code for AcceleratedLinkedList
#include "Backend/qmb/AcceleratedLinkedList.h"
#include <cassert>
#include <iostream>


int main()
{
	qmb::AcceleratedLinkedList<int, int> list;
	list.insert(43, std::move(std::make_unique<int>(65)));

	assert(*(list.get(43)) == 65);

	std::cout << *(list.get(43));




}


*/



#include "Backend/vgui/vgui_event_win32_impl.h"
#include "Backend/vgui/vgui_window.h"
#include "Backend/vgui/vgui_event.h"
#include "Backend/qmb/QMBApplication.h"
#include "Backend/vgui/vgui_background.h"
#include "Backend/vgui/vgui_button.h"
#include "Backend/woodchuck/woodchuck.h"
#include <format>
#include <memory>
using namespace native;
using namespace vgui;

int main(int argc, char** argv)
{
	#ifdef _DEBUG
		woodchuck::init<woodchuck::CLISink>();
	#else
		woodchuck::init<woodchuck::FileSink>("../QuickMenuBuilder.log");
	#endif
		woodchuck::setVerboseMode(false);


	// Make an Windows application
	qmb::QMBApplication app;

	// initialize it
	app.init();

	// make a Windows window, capable of VGUI rendering (this is what took forever)
	vgui::VWindow window(&app);

	app.link_window(window);

	window.init(app, (LPWSTR)L"QuickMenuBuilder v. 0.7", 100, 100, 500, 400);


	window.m_LayerStack.AddWidget<VBackground>("bg", Layer::BACK, window, "C:/Users/devin/Desktop/morty.jpg");
	window.m_LayerStack.AddWidget<VButton>("button", 1);




	MSG msg;



	while (!app.status) {
		while (GetMessage(&msg, nullptr, 0, 0)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);




			if (app.status) break;

		}

	}
}