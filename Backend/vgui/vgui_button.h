#pragma once

#include "vgui_widget.h"
#include "vgui_action.h"
#include <thirdparty/json/json.hpp>
using json = nlohmann::json;
namespace native
{
    struct Application;
}

namespace vgui
{
    struct VButton : vgui::Widget
    {
        Action      m_Action;
        bool        clicked = false;
        
        // By default, just do the action
        void (*m_OnClick_pfn)(native::Application*, VButton*, int, int) = [](native::Application* app, VButton* btn, int x, int y) {

            btn->m_Action.run(app);
        };

        // action binding
        VButton();

        // events
        LRESULT on_event(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) override;

        bool on_event(const Event& evt) override;

    };
}
