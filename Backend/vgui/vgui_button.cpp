#include "vgui_button.h"

namespace vgui
{

    VButton::VButton() {
        m_Action.m_Type = ActionType::EXIT;
        m_Action.m_Args = "";
    }





    bool VButton::on_event(const Event& evt) {

        if (evt.type == EventType::LIFETIME_DTOR_EVENT) {
            std::cout << "VButton got the dtor event\n";
        }

        if (evt.type == EventType::MOUSE_CLICK_EVENT && overlaps(evt.mouse_event.x, evt.mouse_event.y))
        {
            m_Action.run(evt.app);
            return 1; // consumes the event
        }
        return false;
    }
}
