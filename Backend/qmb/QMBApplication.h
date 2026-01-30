#pragma once
#include "../platform/win32/Application.h"
#include "../vgui/vgui_layerstack.h"
#include "../vgui/vgui_event.h"
#include "../vgui/vgui_window.h"


namespace vgui {
	struct LayerStack;
	struct Event;
}

namespace qmb {
	/// <summary>
	/// The QuickMenuBuilder application. Stores a pointer to a vgui window, so it can propagate vgui events
	/// </summary>
	struct QMBApplication : native::Application {
		vgui::VWindow* m_Window = nullptr;

		// Propagates an event to the layerstack
		void fire(const vgui::Event& evt);

		// This application's custom exit logic
		void exit(const std::string& msg) override;

		// Links a vgui window to this application
		void link_window(vgui::VWindow& window);

	};
}