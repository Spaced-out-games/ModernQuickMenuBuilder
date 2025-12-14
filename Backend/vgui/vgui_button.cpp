#include "vgui_button.h"

namespace vgui
{
    void VButton::bindAction(Action_t type, std::string args)
    {
        m_Action = { type, args };
    }

    VButton::VButton(Action_t type, const std::string& args)
        : m_Action(type, args)
    {
    }

    VButton::VButton(json bounds, json action)
        : Widget(bounds), m_Action(action)
    {
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
                m_Action.run(m_Owner, this);
            }
            clicked = false;
        }

        return 0;
    }
}
