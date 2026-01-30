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

    // The type of vgui action we are dealing with
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
        // Which type of vgui action this represents
        ActionType m_Type = ActionType::NONE;

        // Arguments for this action
        json m_Args;

        /// <summary>
        /// Runs the vgui Action
        /// </summary>
        void run(native::Application* app);

    };



}
