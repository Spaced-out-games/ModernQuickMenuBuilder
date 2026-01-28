#pragma once
#include "vgui_layer.h"
#include "vgui_event.h"

namespace vgui
{
	struct LayerStack: qmb::AcceleratedLinkedList<Layer>
	{

		void draw(const Event& evt);
		bool on_event(const Event& evt);
	};
}