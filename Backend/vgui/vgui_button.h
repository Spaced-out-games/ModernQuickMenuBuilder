#pragma once
#include "vgui.h"
#include "vgui_widget.h"
#include "vgui_action.h"


namespace vgui
{
	struct VButton: vgui::Widget
	{
		using interact_pfn_t = void(*)(VButton*, int x, int y);

		Action		   m_Action;

		std::string	   argument;
		bool clicked = false;


		void bindAction(Action_t type, std::string args)
		{
			m_Action = { type, args };
		}


		VButton() = default;
		VButton(Action_t type, const std::string& args): m_Action(type, args)
		{
		}
		VButton(json bounds, json action):Widget(bounds), m_Action(action)
		{

		}




		virtual LRESULT on_event(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) override
		{
			int x = LOWORD(lp);
			int y = HIWORD(lp);
			if (msg == WM_LBUTTONDOWN && overlaps(x, y))
			{
				clicked = overlaps(x, y);
			}
			if (msg == WM_LBUTTONUP &&  overlaps(x, y))
			{
				if (overlaps(x, y) && clicked)
				{
					m_Action.run(m_Owner, this);
				}
				clicked = false;
			}

			return 0;
		}

	};
}