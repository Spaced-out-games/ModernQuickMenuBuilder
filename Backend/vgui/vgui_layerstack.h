#pragma once
#include "vgui_layer.h"
#include "vgui_event.h"
#include <string>

namespace vgui
{
	// Represents a set of widget layers
	struct LayerStack: qmb::AcceleratedLinkedList<std::string, Layer>
	{
		void draw(const Event& evt);
		bool on_event(const Event& evt);
	};
}