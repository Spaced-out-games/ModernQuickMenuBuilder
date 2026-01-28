#include "vgui_event.h"

namespace vgui {
    void makeTickEvent(Event& evt) {
        evt.type = EventType::LIFETIME_TICK_EVENT;
        evt.tick_event.deltaTime = 1.0f / 60.0f; // placeholder
    }
}