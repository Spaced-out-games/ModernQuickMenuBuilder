#pragma once
#include "vgui_layer.h"
#include "vgui_event.h"

namespace vgui
{
	bool layer_sort_fn(const Layer& a, const Layer& b);
	// Represents a set of widget layers
	struct LayerStack: qmb::AcceleratedLinkedList<Layer::depth_t, Layer, layer_sort_fn>
	{

		void draw(const Event& evt);
		bool on_event(const Event& evt);

		template<class widget_t, class... Args>
		void AddWidget(const std::string& name, Layer::depth_t z, Args&&... args) {
			static_assert(std::is_base_of_v<Widget, widget_t>,
				"widget_t must derive from Widget!");

			// check for an existing layer
			Layer* target = get(z);
			// make one if it doesn't exist
			if (!target) {
				insert(z, std::make_unique<Layer>(z));
				target = get(z);
			}

			target->insert(name, std::make_unique<widget_t>(std::forward<Args>(args)...));
		
		}

		Layer::depth_t resolve_z(Layer::depth_t z);

		void DeleteWidget(const std::string& name, Layer::depth_t z);

		Widget* GetWidget(const std::string& name, Layer::depth_t z);

		void MoveWidget(const std::string& name, Layer::depth_t old_z, Layer::depth_t new_z);

		LayerStack();

	};
}