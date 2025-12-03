#pragma once
#include "vgui_widget.h"
#include "vgui_action.h"


namespace vgui
{
	struct VButton: vgui::Widget
	{
		using interact_pfn_t = void(*)(VButton*, int x, int y);

		vgui::Context* m_Owner = nullptr;
		Action		   m_Action;

		std::string	   argument;
		bool clicked = false;


		void bindAction(Action_t type, std::string args)
		{
			m_Action = { type, args };
		}



		virtual LRESULT on_event(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) override
		{
			int x = LOWORD(lp);
			int y = HIWORD(lp);
			if (msg == WM_LBUTTONDOWN && overlaps(x, y))
			{
				clicked = overlaps(x, y);
			}
			//if (msg == WM_MOUSEMOVE && on_mouse_move && overlaps(x, y))
			//{
			//	on_mouse_move(this, LOWORD(lp), HIWORD(lp));
			//}
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