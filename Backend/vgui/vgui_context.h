#pragma once
#include <Windows.h>
#include "vgui_widget.h"
#include <vector>

namespace vgui
{


    struct Context {
        HWND hwnd;
        std::vector<Widget*> widgets;

        void draw(HDC hdc) {
            for (auto w : widgets)
                w->draw(hdc);
        }

        // forward an event to us
        LRESULT on_event(UINT msg, WPARAM wParam, LPARAM lParam)
        {
            LRESULT result = -1;
            for (auto w : widgets)
            {
                result = w->on_event(msg, wParam, lParam);

            }
        }
    };
}