#pragma once
#include <Windows.h>
#include "vgui.h"
#include "thirdparty/json/json.hpp"
#include "vgui_error.h"
using json = nlohmann::json;


namespace vgui
{
    struct Widget {
        vgui::Context* m_Owner = nullptr;
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
        Widget(int x, int y, int w, int h): x(x), y(y), h(h), w(w) {}
        Widget(json bounds)
        {
            using enum vgui::Error;

            if (!bounds.is_array())
            {
                vgui::exit(std::format("Bounds are not an array!"), JSON_PARSE_ERROR);
            }
            if (bounds.size() > 4)
            {
                vgui::exit(std::format("Bounds has too many arguments (4 required)!"), Error::JSON_PARSE_ERROR);
            }
            if (bounds.size() < 4)
            {
                vgui::exit(std::format("Bounds has too many arguments (4 required)!"), Error::JSON_PARSE_ERROR);
            }

            x = bounds[0].get<int>();
            y = bounds[1].get<int>();
            w = bounds[2].get<int>();
            h = bounds[3].get<int>();
        }

        bool overlaps(int px, int py) {
            return px >= x && px <= x + w && py >= y && py <= y + h;
        }



        virtual ~Widget() = default;

    };
}