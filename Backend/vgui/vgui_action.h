#pragma once
#include "vgui_context.h"
#include "vgui_error.h"
#include <string>
#include <cassert>

namespace vgui
{
	// Actions we need:
	//     switch scene(name)
	//     switch background(path)
	//     open a file(path)
	//     exit(message = "")



	enum class Action_t
	{
		NONE,
		EXIT,
		SWITCH_PAGE,
		SWITCH_BACKGROUND,
		OPEN_FILE
	};

	Action_t from_string(const std::string& name)
	{
		using enum Action_t;
		if (name == "") return NONE;
		else if (name == "exit") return EXIT;
		else if (name == "switch_page") return SWITCH_PAGE;
		else if (name == "switch_background") return SWITCH_BACKGROUND;
		else if (name == "open") return OPEN_FILE;


		return NONE;
	}






	struct Action
	{
		Action_t type = Action_t::NONE;
		std::string args = ""; // todo: make into a json for flexibility

		void run(vgui::Context* ctx, vgui::Widget* widget)
		{

			using enum Action_t;
			switch (type)
			{
			case vgui::Action_t::NONE:
				break;
			case vgui::Action_t::EXIT:
				exit(args, Error::SUCCESS_GENERIC);
				break;
			case vgui::Action_t::SWITCH_PAGE:
				assert(ctx != nullptr); // gaurdrail
				ctx->LoadPage(args);

				break;
			case vgui::Action_t::SWITCH_BACKGROUND:
				assert(ctx != nullptr); // gaurdrail
				ctx->LoadBackground("main-menu", args); // TEST VALUE - REPLACE WITH SINGLE-ARG ALTERNATIVE LATER
				ctx->m_Window->redraw_now();


				break;
			case vgui::Action_t::OPEN_FILE:
				assert(0);
				break;
			default:
				std::cout << (int)type;
				// catch what isn't implemented
				assert(0);
				break;
			}






		}
		
		
		// debug only
		Action(const std::string& action_type, const std::string& action_args)
		{
			__debugbreak();
			args = action_args;
			type = from_string(action_type);
		}

		// debug only
		Action(Action_t type, const std::string& args): type(type), args(args)
		{
			__debugbreak();
		}

		Action(json action)
		{

			// just use what is already default
			if (action.is_null() || !action.is_array() || action.size() != 2)
			{
				return;
			}
			if (action[0].is_string())
			{
				type = from_string(action[0].get<std::string>());
			}
			else
			{
				// no type provided, so throw
			}
			
			type = from_string(action[0].get<std::string>());
			args = action[1].get<std::string>();


		}

	};







}