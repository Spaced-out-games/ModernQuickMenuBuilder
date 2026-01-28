#pragma once

#include <Windows.h>
#include "../platform/win32/Image.h"
#include "vgui_widget.h"
namespace native { class WidgetBase; }
namespace qmb { class Image; }
namespace vgui
{
    struct VBackground : vgui::Widget
    {
        // image to draw
        qmb::Image img;

        // rendering
        void draw(HDC hdc) override;

        // sizing
        void stretch_to_fit(HWND hwnd);

        // events
        bool on_event(const Event& evt) override;

        VBackground(native::WidgetBase& window);

    };
}
