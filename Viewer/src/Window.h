#pragma once
#include "WidgetBase.h"

namespace QMB
{
    // Raw C-style callback signature
    using WindowCallback = LRESULT(*)(HWND, WPARAM, LPARAM);

    class Window : public WidgetBase
    {
        static bool registered;

        WindowCallback m_onClose = nullptr;
        WindowCallback m_onPaint = nullptr;
        WindowCallback m_onResize = nullptr;

    protected:
        LRESULT on_event(UINT msg, WPARAM wParam, LPARAM lParam) override
        {
            switch (msg)
            {
            case WM_CLOSE:
                if (m_onClose) return m_onClose(m_Handle, wParam, lParam);
                PostQuitMessage(0); // default behavior
                return 0;

            case WM_PAINT:
                if (m_onPaint) return m_onPaint(m_Handle, wParam, lParam);
                break;

            case WM_SIZE:
                if (m_onResize) return m_onResize(m_Handle, wParam, lParam);
                break;
            }

            // fallback to base class
            return WidgetBase::on_event(msg, wParam, lParam);
        }

    public:
        Window() = default;

        void init(
            HINSTANCE application,
            LPWSTR title,
            int x, int y, int w, int h,
            WindowCallback onClose = nullptr,
            WindowCallback onPaint = nullptr,
            WindowCallback onResize = nullptr
        )
        {
            m_onClose = onClose;
            m_onPaint = onPaint;
            m_onResize = onResize;

            init_impl(
                registered,
                0,                 // styleExtended
                (LPWSTR)L"QMB_Window",      // class_name
                title,             // window title
                WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                x, y, w, h,
                nullptr,           // no parent
                nullptr,           // no menu
                application,
                IDC_ARROW,         // default cursor
                (HBRUSH)(COLOR_WINDOW + 1) // default background
            );
        }
    };

    bool Window::registered = false;
}
