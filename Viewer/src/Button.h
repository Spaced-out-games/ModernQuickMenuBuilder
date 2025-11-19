#pragma once
#include "WidgetBase.h"

namespace QMB
{
    // Raw C-style callback signature
    using ButtonCallback = LRESULT(*)(HWND, WPARAM, LPARAM);

    class Button : public WidgetBase
    {
        static bool registered;

        ButtonCallback m_onClick = nullptr;
        ButtonCallback m_onRelease = nullptr;
        ButtonCallback m_onHover = nullptr;

    protected:
        // Internal event handler
        LRESULT on_event(UINT msg, WPARAM wParam, LPARAM lParam) override
        {
            switch (msg)
            {
            case WM_LBUTTONDOWN:
                if (m_onClick) return m_onClick(m_Handle, wParam, lParam);
                break;

            case WM_LBUTTONUP:
                if (m_onRelease) return m_onRelease(m_Handle, wParam, lParam);
                break;

            case WM_MOUSEMOVE:
                if (m_onHover) return m_onHover(m_Handle, wParam, lParam);
                break;
            }

            // Fallback to base behavior
            return WidgetBase::on_event(msg, wParam, lParam);
        }

    public:
        Button() = default;

        void init(
            HWND parent,
            HINSTANCE application,
            int x, int y, int w, int h,
            ButtonCallback onClick = nullptr,
            ButtonCallback onRelease = nullptr,
            ButtonCallback onHover = nullptr
        )
        {
            m_onClick = onClick;
            m_onRelease = onRelease;
            m_onHover = onHover;

            // Use base init_impl to create the window
            init_impl(
                registered,
                0,                        // styleExtended
                (LPWSTR)L"QMB_Button",             // class_name
                (LPWSTR)L"Button",                 // text
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, // style
                x, y, w, h,
                parent,
                nullptr,                  // menu
                application,
                IDC_ARROW,                // cursor
                (HBRUSH)(COLOR_BTNFACE + 1) // background brush
            );
        }
    };

    // Define the static bool
    bool Button::registered = false;
}
