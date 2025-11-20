#pragma once
#include "WidgetBase.h"
#include <commctrl.h>
#include <windows.h>
#pragma comment(lib, "comctl32.lib")
namespace QMB
{

    LRESULT CALLBACK WidgetSubclassProc(
        HWND hwnd,
        UINT msg,
        WPARAM wParam,
        LPARAM lParam,
        UINT_PTR subclassId,
        DWORD_PTR refData)
    {
        WidgetBase* widget = reinterpret_cast<WidgetBase*>(refData);

        if (widget)
        {
            LRESULT r = widget->on_event(msg, wParam, lParam);
            if (r != 0)
                return r;
        }

        return DefSubclassProc(hwnd, msg, wParam, lParam);
    }
    // Raw C-style callback signature
    //using ButtonCallback = LRESULT(*)(HWND, WPARAM, LPARAM);

    class Button : public WidgetBase
    {
        // whether button widget type has been registered
        inline static bool registered = true;

        // 
        callback_t m_onClick = nullptr;
        callback_t m_onRelease = nullptr;
        callback_t m_onHover = nullptr;

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
            callback_t onClick = nullptr,
            callback_t onRelease = nullptr,
            callback_t onHover = nullptr
        )
        {
            registered = true;
            m_onClick = onClick;
            m_onRelease = onRelease;
            m_onHover = onHover;

            init_impl(
                registered,
                0,                          // extended style
                (LPWSTR)L"BUTTON",          // USE REAL BUTTON CLASS
                (LPWSTR)L"Button",          // text on the button
                WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON,
                x, y, w, h,
                parent,
                nullptr,                    // HMENU = nullptr? -> you should pass an ID later
                application,
                IDC_ARROW,
                nullptr
            );
            SetWindowSubclass(m_Handle, WidgetSubclassProc, 1, reinterpret_cast<DWORD_PTR>(this));

        }
    };

    // Define the static bool
}
