#pragma once
#include "vgui_event.h"
#include <queue>

namespace vgui
{

	// Manages population and flushing of event queues.
	struct EventContext
	{
		std::queue<Event> m_Events;
		// Might want to make this agnostic by making it a wrapped function pointer instead...
		void (*pollEvents)(EventContext* self) = nullptr;
	};
}