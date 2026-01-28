#include "vgui_button.h"

namespace vgui
{

    VButton::VButton() {
        m_Action.m_Type = ActionType::EXIT;
        m_Action.m_Args = "";
    }



    LRESULT VButton::on_event(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
    {
        int x = LOWORD(lp);
        int y = HIWORD(lp);

        if (msg == WM_LBUTTONDOWN && overlaps(x, y))
        {
            clicked = true;
        }

        if (msg == WM_LBUTTONUP)
        {
            if (overlaps(x, y) && clicked)
            {
                __debugbreak();
                //m_Action.run(m_Owner, this);
            }
            clicked = false;
        }

        return 0;
    }

    bool VButton::on_event(const Event& evt) {

        if (evt.type == EventType::LIFETIME_DTOR_EVENT) {
            std::cout << "VButton got the dtor event";
        }

        if (evt.type == EventType::MOUSE_CLICK_EVENT && overlaps(evt.mouse_event.x, evt.mouse_event.y))
        {
            if (m_OnClick_pfn)
            {
                m_OnClick_pfn(evt.app, this, evt.mouse_event.x, evt.mouse_event.y);
            }
            else
            {
                throw std::runtime_error("m_OnClick_pfn was nullptr.");
            }
            return 1; // consumes the event
        }
        return false;
    }
}
