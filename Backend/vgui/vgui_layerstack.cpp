#include "vgui_layerstack.h"

namespace vgui
{

	bool layer_sort_fn(const Layer& a, const Layer& b) {
		return a.z > b.z;
	}

	void LayerStack::draw(const Event& evt)
	{
		for (auto it = rbegin(); it != rend(); ++it) {
			it->draw(evt);
		}
	}
	bool LayerStack::on_event(const Event& evt) {



		if (evt.type == EventType::WINDOW_PAINT_EVENT) {
			draw(evt);
			return 0;
		}


		for (auto it = begin(); it != end(); ++it) {
			if ((*it).on_event(evt)) return 1;
		}

		return 0; // breakpoint jumps here for some reason.
	}

	Layer::depth_t LayerStack::resolve_z(Layer::depth_t z)
	{
		if (!size()) return Layer::INVALID_LAYER;
		switch (z) {
		case Layer::FRONT:
			return rbegin()->z;

		case Layer::BACK:
			return begin()->z;

		default:
			return z;
		}
	}

	void LayerStack::DeleteWidget(const std::string& name, Layer::depth_t z) {
		if (!size()) return;
		Layer* target = nullptr;

		z = resolve_z(z);
		target = get(z);
		if (!target) return;
		if (!target->contains(name)) return;
		target->remove(name);
	}

	Widget* LayerStack::GetWidget(const std::string& name, Layer::depth_t z)
	{
		if (!size()) return nullptr;
		z = resolve_z(z);
		Layer* target = get(z);
		if (!target) return nullptr;
		return target->get(name);
	}
	LayerStack::LayerStack() {

	}


	void LayerStack::MoveWidget(const std::string& name, Layer::depth_t old_z, Layer::depth_t new_z) {
		if (!size()) return;
		old_z = resolve_z(old_z);
		new_z = resolve_z(new_z);

		Layer* old_layer = get(old_z);
		if (!old_layer) return; // nothing to move



		// Take ownership of the widget
		std::unique_ptr<Widget> widget = old_layer->take(name);
		if (!widget) return; // widget didn't exist

		// Ensure the new layer exists
		Layer* new_layer = get(new_z);
		if (!new_layer) {
			insert(new_z, std::make_unique<Layer>(new_z));
			new_layer = get(new_z);
		}

		// Insert the widget into the new layer
		new_layer->insert(name, std::move(widget));
	}






}