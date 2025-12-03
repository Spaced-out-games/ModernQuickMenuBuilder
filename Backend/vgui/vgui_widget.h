#pragma once
#include <Windows.h>
#include "vgui.h"


namespace vgui
{
    struct Widget {
        int x = 0, y = 0, w = 20, h = 20;
        virtual void draw(HDC hdc)
        {
            if (!vgui::g_Debug) return;
            HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));
            HPEN oldPen = (HPEN)SelectObject(hdc, GetStockObject(BLACK_PEN));

            Rectangle(hdc, x, y, x + w, y + h);

            // Restore original objects (important!)
            SelectObject(hdc, oldBrush);
            SelectObject(hdc, oldPen);
        }
        virtual LRESULT on_event(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
        {
            if (msg == WM_SIZE)
            {
                InvalidateRect(hwnd, NULL, TRUE);
            }
            return 0;
        }

        Widget() = default;

        bool overlaps(int px, int py) {
            return px >= x && px <= x + w && py >= y && py <= y + h;
        }


        virtual ~Widget() = default;

    };
}