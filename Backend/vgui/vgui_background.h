#pragma once
#include "../native/Image.h"
#include "vgui_widget.h"
#include <Windows.h>
#include "../overrides/ui.h"
#include "vgui.h"



namespace vgui
{
	struct VBackground : vgui::Widget
	{
		qmb::Image img = {};

		void draw(HDC hdc) override
		{

			if(vgui::g_Debug) Rectangle(hdc, 0, 0, w, h);
			
			
			img.draw(hdc, 0, 0, w, h);
			

		}

		void stretch_to_fit(HWND hwnd)
		{
			RECT rc{};
			if (!GetClientRect(hwnd, &rc))
				return;

			w = rc.right - rc.left;
			h = rc.bottom - rc.top;

			InvalidateRect(hwnd, nullptr, TRUE);
		}

		LRESULT on_event(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) override
		{
			
			if (msg == WM_SIZE)
			{
				w = LOWORD(lp);
				h = HIWORD(lp);
				InvalidateRect(hwnd, NULL, TRUE);
			}
			if (msg == WM_DROPFILES)
			{
				ui::drag_drop_bg_img(hwnd, img, wp, lp);
			}



			return 0;
		}


		
	};
}