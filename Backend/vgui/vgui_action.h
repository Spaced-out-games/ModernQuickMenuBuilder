#pragma once
#include "vgui_context.h"
#include <string>

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
		SWITCH_SCENE,
		SWITCH_BACKGROUND,
		OPEN_FILE
	};

	struct Action
	{
		Action_t type;
		std::string args;

		void run(vgui::Context* ctx, vgui::Widget* widget)
		{
			using enum Action_t;
			switch (type)
			{
			case vgui::Action_t::NONE:
				break;
			case vgui::Action_t::EXIT:
				std::cout << args;
				exit(0);

				break;
			case vgui::Action_t::SWITCH_SCENE:
				assert(ctx != nullptr); // gaurdrail

				break;
			case vgui::Action_t::SWITCH_BACKGROUND:
				assert(ctx != nullptr); // gaurdrail
				break;
			case vgui::Action_t::OPEN_FILE:
				break;
			default:
				break;
			}




		}

	};







}