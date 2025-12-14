#pragma once

#include <Windows.h>
#include "../native/Image.h"
#include "vgui_widget.h"

namespace qmb { class Image; }

namespace vgui
{
    struct VBackground : vgui::Widget
    {
        qmb::Image img;

        // rendering
        void draw(HDC hdc) override;

        // sizing
        void stretch_to_fit(HWND hwnd);

        // events
        LRESULT on_event(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) override;
    };
}
