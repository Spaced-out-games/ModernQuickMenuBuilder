#include "vgui_layerstack.h"

namespace vgui
{
	void LayerStack::draw(const Event& evt)
	{
		for (auto& layer : *this) {
			layer.draw(evt);
		}
	}
	bool LayerStack::on_event(const Event& evt) {



		if (evt.type == EventType::WINDOW_PAINT_EVENT) {
			draw(evt);
			return 0;
		}


		

		for (auto& layer : *this) { // start here
			layer.on_event(evt);
		}
		return 0; // breakpoint jumps here for some reason.
	}
}