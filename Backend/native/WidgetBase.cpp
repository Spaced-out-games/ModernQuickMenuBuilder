#include "WidgetBase.h"
#include <cassert>

namespace native
{
    LRESULT EventDelegate(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        void* data = (void*)GetWindowLongPtr(hwnd, GWLP_USERDATA);


        // Copy `this`, stored in lParam, to the userdata slot. At this point, the long pointer isn't actually set.
        if (!data && msg == WM_NCCREATE)
        {
            CREATESTRUCTW* cs = (CREATESTRUCTW*)lParam;

            data = cs->lpCreateParams;
            
            // Sets the user data
            SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)data);
            
            // slightly early exit
            return DefWindowProc(hwnd, msg, wParam, lParam);

        }

        WidgetBase* widget = (WidgetBase*)data;

        if (widget)
        {
            widget->on_event(msg, wParam, lParam);
        }

        return DefWindowProc(hwnd, msg, wParam, lParam);
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

    RECT WidgetBase::bounds() const
    {
        RECT rect;
        GetClientRect(m_Handle, &rect);
        return rect;
    }

    HWND WidgetBase::handle() const { return m_Handle; };







    



    /////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////










    void WidgetBase::show() const
    {
        ShowWindow(m_Handle, SW_SHOW);
    }

    void WidgetBase::hide() const
    {
        ShowWindow(m_Handle, SW_HIDE);
    }

    void WidgetBase::enable() const
    {
        EnableWindow(m_Handle, TRUE);
    }

    void WidgetBase::disable() const
    {
        EnableWindow(m_Handle, FALSE);
    }

    void WidgetBase::resize(int new_width, int new_height) const
    {
        SetWindowPos(m_Handle, nullptr,
            0, 0,
            new_width, new_height,
            SWP_NOMOVE | SWP_NOZORDER);
    }

    void WidgetBase::move(int new_X, int new_Y) const
    {
        SetWindowPos(m_Handle, nullptr,
            new_X, new_Y,
            0, 0,
            SWP_NOSIZE | SWP_NOZORDER);
    }

    void WidgetBase::move_forward() const
    {
        SetWindowPos(m_Handle, HWND_TOP,
            0, 0, 0, 0,
            SWP_NOMOVE | SWP_NOSIZE);
    }

    void WidgetBase::move_backward() const
    {
        SetWindowPos(m_Handle, HWND_BOTTOM,
            0, 0, 0, 0,
            SWP_NOMOVE | SWP_NOSIZE);
    }

    std::string WidgetBase::text() const
    {
        int len = GetWindowTextLengthA(m_Handle);
        std::string result(len, '\0');

        if (len > 0)
            GetWindowTextA(m_Handle, result.data(), len + 1);

        return result;
    }

    void WidgetBase::text(const std::string& txt) const
    {
        SetWindowTextA(m_Handle, txt.c_str());
    }

    void WidgetBase::invalidate() const
    {
        InvalidateRect(m_Handle, nullptr, TRUE);
    }

    void WidgetBase::redraw_now() const
    {
        // Forces immediate WM_PAINT
        RedrawWindow(m_Handle, nullptr, nullptr,
            RDW_INVALIDATE | RDW_UPDATENOW);
    }

    void WidgetBase::focus(bool set) const
    {
        if (set)
            SetFocus(m_Handle);
        else
            SetFocus(nullptr);
    }

    bool WidgetBase::focus() const
    {
        return GetFocus() == m_Handle;
    }

    void WidgetBase::capture() const
    {
        SetCapture(m_Handle);
    }

    void WidgetBase::release() const
    {
        ReleaseCapture();
    }

}