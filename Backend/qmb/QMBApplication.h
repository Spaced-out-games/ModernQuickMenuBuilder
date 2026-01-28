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
	struct QMBApplication : native::Application {
		vgui::VWindow* m_Window = nullptr;
		// Stores all the layers
		//vgui::LayerStack m_LayerStack;
		void fire(const vgui::Event& evt);

		void exit(const std::string& msg) override;

		void link_window(vgui::VWindow& window);

	};
}