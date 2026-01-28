#pragma once

#include <string>
#include "thirdparty/json/json.hpp"

using json = nlohmann::json;

namespace native
{
    struct Application;
}

namespace vgui
{


    enum class ActionType
    {
        NONE,
        EXIT,
        SWITCH_PAGE,
        SWITCH_BACKGROUND,
        OPEN_FILE
    };


    struct Action
    {
        ActionType m_Type = ActionType::NONE;
        json m_Args;

        void run(native::Application* app);

    };

    // for each ActionType, forward declare a free function, define them in vgui_action.cpp,
    // and pass arguments to them in Action::run().

    namespace action
    {
        // gives a dtor event to each widget in the window, frees the layerstack, and exits the application 
        void exit(native::Application*, const std::string&);
    }


}
