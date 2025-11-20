#pragma once
#include "WidgetBase.h"
#include "Image.h"

namespace QMB
{
    // Raw C-style callback signature
    using WindowCallback = LRESULT(*)(HWND, WPARAM, LPARAM);

    class Window : public WidgetBase
    {
        inline static bool registered = false;
        

        WindowCallback m_onClose = nullptr;
        WindowCallback m_onPaint = nullptr;
        WindowCallback m_onResize = nullptr;
        WindowCallback m_onFileDrop = nullptr;


    protected:
        LRESULT on_event(UINT msg, WPARAM wParam, LPARAM lParam) override;

    public:
        Image img = {}; // btw this is a test. Use something better, dumbass.
        Image display = {}; // btw this is a test. Use something better, dumbass.

        Window() = default;
        Window(HWND handle);

        void init(
            HINSTANCE application,
            LPWSTR title,
            int x, int y, int w, int h,
            WindowCallback onClose = nullptr,
            WindowCallback onPaint = nullptr,
            WindowCallback onResize = nullptr,
            WindowCallback onFileDrop = nullptr

        );
    };
}
