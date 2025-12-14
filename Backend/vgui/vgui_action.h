#pragma once

#include <string>
#include "thirdparty/json/json.hpp"

namespace vgui
{
    struct Context;
    struct Widget;

    enum class Action_t
    {
        NONE,
        EXIT,
        SWITCH_PAGE,
        SWITCH_BACKGROUND,
        OPEN_FILE
    };

    Action_t from_string(const std::string& name);

    struct Action
    {
        Action_t type = Action_t::NONE;
        std::string args;

        Action() = default;

        // debug-only helpers
        Action(const std::string& action_type, const std::string& action_args);
        Action(Action_t type, const std::string& args);

        // JSON-driven constructor
        explicit Action(nlohmann::json action);

        void run(Context* ctx, Widget* widget);
    };
}
