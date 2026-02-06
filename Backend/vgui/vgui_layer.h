#pragma once
#include "../qmb/AcceleratedLinkedList.h"
#include "vgui_widget.h"
#include "vgui_event.h"
#include <limits>
#include <string>
#undef min
#undef max

namespace vgui
{




	// Represents a set of sister widgets that should never overlap
	struct Layer : qmb::AcceleratedLinkedList<std::string, Widget> {
		using depth_t = int;
		static constexpr depth_t FRONT = std::numeric_limits<depth_t>::max();
		static constexpr depth_t BACK = std::numeric_limits<depth_t>::min();
		static constexpr depth_t INVALID_LAYER = std::numeric_limits<depth_t>::max() - 1;
		depth_t z = BACK;
		bool operator<(const Layer& rhs) const { return z < rhs.z; } // this might be the wrong sign
		Layer() = default;
		Layer(depth_t z) : z(z) {}

		bool on_event(const Event& evt) {

			//for (auto& widget : *this) {
			//	if (widget.on_event(evt)) return 1;
			//}

			for (auto it = begin(); it != end(); ++it) {
				if ((*it).on_event(evt)) return 1;
			}

			return 0;
		}


		void draw(const Event& evt) {
			for (auto it = rbegin(); it != rend(); ++it) {
				it->draw((HDC)evt.window_paint_event.device);
			}

		}


	};

}