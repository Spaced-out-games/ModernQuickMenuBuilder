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
    // vgui button. Calls a callback. By default
    struct VButton : vgui::Widget
    {
        VButton();
        Action      m_Action;
        bool        clicked = false;


        bool on_event(const Event& evt) override;

    };
}
