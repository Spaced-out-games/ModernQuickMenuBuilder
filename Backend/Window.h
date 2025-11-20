#pragma once
#include "WidgetBase.h"
#include "Image.h"
#include "WidgetCallback.h"

namespace QMB
{
    // Raw C-style callback signature

    class Window : public WidgetBase
    {
        inline static bool registered = false;
        




    protected:

    public:
        Image img = {}; // btw this is a test. Use something better, dumbass.
        Image display = {}; // btw this is a test. Use something better, dumbass.

        Window() = default;
        Window(HWND handle);

        void init(
            HINSTANCE application,
            LPWSTR title,
            int x, int y, int w, int h);
    };
}
