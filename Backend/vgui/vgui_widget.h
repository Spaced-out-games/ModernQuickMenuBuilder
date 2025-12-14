#pragma once

#include <Windows.h>
#include <string>
#include "thirdparty/json/json_fwd.hpp"

namespace vgui
{
    struct Context;

    struct Widget
    {
        Context* m_Owner = nullptr;
        int x = 0;
        int y = 0;
        int w = 20;
        int h = 20;

        Widget();
        Widget(int x, int y, int w, int h);
        explicit Widget(nlohmann::json bounds);

        virtual void draw(HDC hdc);
        virtual LRESULT on_event(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

        bool overlaps(int px, int py) const;

        virtual ~Widget();
    };
}
