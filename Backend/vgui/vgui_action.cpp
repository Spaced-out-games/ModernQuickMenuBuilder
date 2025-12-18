#include "vgui_action.h"

#include "vgui_context.h"
#include "vgui_error.h"
#include "vgui_window.h"

#include <cassert>
#include <iostream>

using json = nlohmann::json;

namespace vgui
{
    Action_t from_string(const std::string& name)
    {
        using enum Action_t;

        if (name.empty()) return NONE;
        if (name == "exit") return EXIT;
        if (name == "switch_page") return SWITCH_PAGE;
        if (name == "switch_background") return SWITCH_BACKGROUND;
        if (name == "open") return OPEN_FILE;

        return NONE;
    }

    void Action::run(Context* ctx, Widget*)
    {
        using enum Action_t;

        switch (type)
        {
        case NONE:
            break;

        case EXIT:
            vgui::exit(args, Error::SUCCESS_GENERIC);
            break;

        case SWITCH_PAGE:
            assert(ctx != nullptr);
            assert(false && "SWITCH_PAGE not implemented");
            //ctx->LoadPage(args);
            break;

        case SWITCH_BACKGROUND:
            assert(ctx != nullptr);
            assert(false && "SWITCH_BACKGROUND not implemented");
            //ctx->LoadBackground("main-menu", args); // TODO: remove hardcode
            //ctx->m_Window->redraw_now();
            break;

        case OPEN_FILE:
            assert(false && "OPEN_FILE not implemented");
            break;

        default:
            std::cout << static_cast<int>(type);
            assert(false && "Unhandled Action_t");
            break;
        }
    }

    // debug-only
    Action::Action(const std::string& action_type, const std::string& action_args)
        : type(from_string(action_type)), args(action_args)
    {
        __debugbreak();
    }

    // debug-only
    Action::Action(Action_t type_, const std::string& args_)
        : type(type_), args(args_)
    {
        //__debugbreak();
    }

    Action::Action(json action)
    {
        if (action.is_null() || !action.is_array() || action.size() != 2)
        {
            return;
        }

        if (!action[0].is_string())
        {
            return; // invalid type
        }

        type = from_string(action[0].get<std::string>());

        if (action[1].is_string())
        {
            args = action[1].get<std::string>();
        }
    }
}
