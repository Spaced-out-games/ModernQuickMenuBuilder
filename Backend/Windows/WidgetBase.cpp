#include "WidgetBase.h"
#include <cassert>

namespace Windows
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

    LRESULT WidgetBase::on_event(UINT msg, WPARAM wParam, LPARAM lParam)
    {
        switch (msg)
        {
            // -------------------- PAINT --------------------
        case WM_PAINT:
        {
            if (m_Callbacks.on_paint)
                return m_Callbacks.on_paint(this, wParam, lParam);
            break;
        }

        // -------------------- RESIZE --------------------
        case WM_SIZE:
            if (m_Callbacks.on_resize)
                return m_Callbacks.on_resize(this, wParam, lParam);
            break;

            // -------------------- CONTEXT MENU ---------------
        case WM_CONTEXTMENU:
            if (m_Callbacks.on_context_menu)
                return m_Callbacks.on_context_menu(this, wParam, lParam);
            break;

            // -------------------- MOUSE MOVE -----------------
        case WM_MOUSEMOVE:
        {
            // Only required extra step: TrackMouseEvent enables WM_MOUSELEAVE
            TRACKMOUSEEVENT tme = { sizeof(TRACKMOUSEEVENT) };
            tme.dwFlags = TME_LEAVE;
            tme.hwndTrack = m_Handle;
            TrackMouseEvent(&tme);

            if (m_Callbacks.on_mouse_move)
                return m_Callbacks.on_mouse_move(this, wParam, lParam);
            break;
        }

        // -------------------- MOUSE LEAVE ----------------
        case WM_MOUSELEAVE:
            if (m_Callbacks.on_mouse_exit)
                return m_Callbacks.on_mouse_exit(this, wParam, lParam);
            break;

            // -------------------- LEFT BUTTON ----------------
        case WM_LBUTTONDOWN:
            if (m_Callbacks.on_mouse_down_L)
                return m_Callbacks.on_mouse_down_L(this, wParam, lParam);
            break;

        case WM_LBUTTONUP:
            if (m_Callbacks.on_mouse_up_L)
                return m_Callbacks.on_mouse_up_L(this, wParam, lParam);
            break;

            // -------------------- RIGHT BUTTON ---------------
        case WM_RBUTTONDOWN:
            if (m_Callbacks.on_mouse_down_R)
                return m_Callbacks.on_mouse_down_R(this, wParam, lParam);
            break;

        case WM_RBUTTONUP:
            if (m_Callbacks.on_mouse_up_R)
                return m_Callbacks.on_mouse_up_R(this, wParam, lParam);
            break;

            // -------------------- FOCUS ----------------------
        case WM_SETFOCUS:
            if (m_Callbacks.on_focus)
                return m_Callbacks.on_focus(this, wParam, lParam);
            break;

        case WM_KILLFOCUS:
            if (m_Callbacks.on_unfocus)
                return m_Callbacks.on_unfocus(this, wParam, lParam);
            break;

            // -------------------- KEYBOARD -------------------
        case WM_KEYDOWN:
            if (m_Callbacks.on_key_down)
                return m_Callbacks.on_key_down(this, wParam, lParam);
            break;

        case WM_KEYUP:
            if (m_Callbacks.on_key_up)
                return m_Callbacks.on_key_up(this, wParam, lParam);
            break;

        case WM_CHAR:
            if (m_Callbacks.on_char)
                return m_Callbacks.on_char(this, wParam, lParam);
            break;

            // -------------------- CONSTRUCT / DESTRUCT -------
        case WM_NCCREATE:
            if (m_Callbacks.on_construct)
                return m_Callbacks.on_construct(this, wParam, lParam);
            break;

        case WM_NCDESTROY:
            if (m_Callbacks.on_destruct)
                return m_Callbacks.on_destruct(this, wParam, lParam);
            break;
        case WM_DROPFILES:
            if (m_Callbacks.on_file_drop)
                return m_Callbacks.on_file_drop(this, wParam, lParam);
            break;
        }

        return 0;
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








    ///                                                 ///
    ///                     getters                     ///
    ///                                                 ///
    HWND WidgetBase::handle() const { return m_Handle; };

    event_pfn_t WidgetBase::on_file_drop() { return m_Callbacks.on_file_drop; }
    paint_pfn_t WidgetBase::on_paint(){ return m_Callbacks.on_paint;}
    mouse_pfn_t WidgetBase::on_mouse_enter(){ return m_Callbacks.on_mouse_enter;}
    mouse_pfn_t WidgetBase::on_mouse_exit(){ return m_Callbacks.on_mouse_exit;}
    mouse_pfn_t WidgetBase::on_mouse_move(){ return m_Callbacks.on_mouse_move;}
    mouse_pfn_t WidgetBase::on_mouse_down_L(){ return m_Callbacks.on_mouse_down_L;}
    mouse_pfn_t WidgetBase::on_mouse_up_L(){ return m_Callbacks.on_mouse_up_L;}
    mouse_pfn_t WidgetBase::on_mouse_down_R(){ return m_Callbacks.on_mouse_down_R ;}
    mouse_pfn_t WidgetBase::on_mouse_up_R(){ return m_Callbacks.on_mouse_up_R;}

    event_pfn_t WidgetBase::on_resize(){ return m_Callbacks.on_resize;}
    event_pfn_t WidgetBase::on_context_menu(){ return m_Callbacks.on_context_menu;}
    event_pfn_t WidgetBase::on_focus(){ return m_Callbacks.on_focus;}
    event_pfn_t WidgetBase::on_unfocus(){ return m_Callbacks.on_unfocus;}
    event_pfn_t WidgetBase::on_key_down(){ return m_Callbacks.on_key_down;}
    event_pfn_t WidgetBase::on_key_up(){ return m_Callbacks.on_key_up;}
    event_pfn_t WidgetBase::on_char(){ return m_Callbacks.on_char;}
    event_pfn_t WidgetBase::on_construct(){ return m_Callbacks.on_construct;}
    event_pfn_t WidgetBase::on_destruct(){ return m_Callbacks.on_destruct;}
    void WidgetBase::begin_paint(PAINTSTRUCT& ps, HDC& hdc)
    {
        hdc = BeginPaint(m_Handle, &ps);
    }
    void WidgetBase::end_paint(PAINTSTRUCT& ps) { EndPaint(m_Handle, &ps); }



    ///                                                 ///
    ///                     setters                     ///
    ///                                                 ///
    void WidgetBase::on_file_drop(event_pfn_t callback) { m_Callbacks.on_file_drop = callback; }
    void WidgetBase::on_paint(paint_pfn_t callback) {m_Callbacks.on_paint = callback;}
    void WidgetBase::on_mouse_enter(mouse_pfn_t callback) {m_Callbacks.on_mouse_enter = callback;}
    void WidgetBase::on_mouse_exit(mouse_pfn_t callback) {m_Callbacks.on_mouse_exit = callback;}
    void WidgetBase::on_mouse_move(mouse_pfn_t callback) {m_Callbacks.on_mouse_move = callback;}
    void WidgetBase::on_mouse_down_L(mouse_pfn_t callback) {m_Callbacks.on_mouse_down_L = callback;}
    void WidgetBase::on_mouse_up_L(mouse_pfn_t callback) {m_Callbacks.on_mouse_up_L = callback;}
    void WidgetBase::on_mouse_down_R(mouse_pfn_t callback) {m_Callbacks.on_mouse_down_R = callback;}
    void WidgetBase::on_mouse_up_R(mouse_pfn_t callback) {m_Callbacks.on_mouse_up_R = callback;}



    void WidgetBase::on_resize(event_pfn_t callback) {m_Callbacks.on_resize = callback;}
    void WidgetBase::on_context_menu(event_pfn_t callback) {m_Callbacks.on_context_menu = callback;}
    void WidgetBase::on_focus(event_pfn_t callback) {m_Callbacks.on_focus = callback;}
    void WidgetBase::on_unfocus(event_pfn_t callback) {m_Callbacks.on_unfocus = callback;}
    void WidgetBase::on_key_down(event_pfn_t callback) {m_Callbacks.on_key_down = callback;}
    void WidgetBase::on_key_up(event_pfn_t callback) {m_Callbacks.on_key_up = callback;}
    void WidgetBase::on_char(event_pfn_t callback) {m_Callbacks.on_char = callback;}
    void WidgetBase::on_construct(event_pfn_t callback) {m_Callbacks.on_construct = callback;}
    void WidgetBase::on_destruct(event_pfn_t callback) {m_Callbacks.on_destruct = callback;}



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