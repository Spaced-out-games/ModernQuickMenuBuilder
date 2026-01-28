#pragma once
#include "../qmb/AcceleratedLinkedList.h"
#include "vgui_widget.h"
#include "vgui_event.h"


namespace vgui
{

	struct Layer : qmb::AcceleratedLinkedList<Widget> {
		int z = INT_MIN;
		bool operator<(const Layer& rhs) const { return z < rhs.z; }
		Layer() = default;
		Layer(int z) : z(z) {}

		bool on_event(const Event& evt) {

			for (auto& widget : *this) {
				if (widget.on_event(evt)) return 1;
			}

			return 0;
		}


		void draw(const Event& evt) {
			for (auto& widget : *this) {
				widget.draw((HDC)evt.window_paint_event.device);
			}
		}


	};

}