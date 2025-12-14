#pragma once

#include "vgui_widget.h"
#include "vgui_action.h"
#include <thirdparty/json/json.hpp>
using json = nlohmann::json;


namespace vgui
{
    struct VButton : vgui::Widget
    {
        using interact_pfn_t = void(*)(VButton*, int x, int y);

        Action      m_Action;
        bool        clicked = false;

        // action binding
        void bindAction(Action_t type, std::string args);

        // constructors
        VButton() = default;
        VButton(Action_t type, const std::string& args);
        VButton(json bounds, json action);

        // events
        LRESULT on_event(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) override;
    };
}
