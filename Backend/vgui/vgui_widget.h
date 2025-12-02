#pragma once
#include <Windows.h>


namespace vgui
{
    struct Widget {
        int x = 0, y = 0, width = 0, height = 0;

        virtual void draw(HDC hdc)
        {

        }
        virtual LRESULT on_event(UINT msg, WPARAM wParam, LPARAM lParam)
        {
            return 0;
        }

        virtual ~Widget() = default;

    };
}