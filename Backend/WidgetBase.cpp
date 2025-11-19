#include "WidgetBase.h"
#include <cassert>

namespace QMB
{
    LRESULT EventDelegate(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        WidgetBase* widget = (WidgetBase*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

        if (!widget && msg == WM_NCCREATE)
        {
            CREATESTRUCTW* cs = (CREATESTRUCTW*)lParam;
            widget = (WidgetBase*)cs->lpCreateParams;   // this is the pointer passed to CreateWindowExW
            SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)widget);
        }

        if (widget)
        {
            widget->on_event(msg, wParam, lParam);
        }

        return DefWindowProc(hwnd, msg, wParam, lParam);
    }

    WidgetBase::operator bool() const
    {
        return m_Handle;
    }

    WidgetBase::operator HWND() const
    {
        return m_Handle;
    }



    void WidgetBase::init_impl(
        bool& registered,
        DWORD styleExtended,
        LPWSTR class_name,
        LPWSTR name,
        DWORD style,
        int x,
        int y,
        int w,
        int h,
        HWND parent,
        HMENU menu,
        HINSTANCE application,
        LPWSTR cursor_id,
        HBRUSH bg_brush
    ) {

        if (!registered)
        {
            if (!application)
                application = GetModuleHandleW(nullptr);  // default: our executable

            if (!cursor_id)
                cursor_id = IDC_ARROW;                    // default: arrow cursor

            WNDCLASSW wc = {};
            wc.lpfnWndProc = EventDelegate;
            wc.hInstance = application;
            wc.lpszClassName = class_name;
            wc.hCursor = LoadCursorW(nullptr, cursor_id);
            wc.hbrBackground = bg_brush ? bg_brush : (HBRUSH)(COLOR_WINDOW + 1);

            RegisterClassW(&wc);
            registered = true;
        }

        m_Handle = CreateWindowExW(
            styleExtended,
            class_name,
            name,
            style,
            x, y, w, h,
            parent,
            menu,
            application,
            this
        );   // extra data

        assert(m_Handle != nullptr);

    }








}