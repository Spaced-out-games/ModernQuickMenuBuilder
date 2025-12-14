#include "vgui_window.h"
#include "../vgui/vgui_context.h"


namespace vgui
{
	void VWindow::begin_paint(PAINTSTRUCT& ps, HDC& hdc)
	{
		begin_paint_impl(m_Handle, ps, hdc);
	}
	void VWindow::end_paint(PAINTSTRUCT& ps)
	{
		end_paint_impl(m_Handle, ps);

	}

	VWindow::VWindow(Context* vgui_context) : m_vguiContext(vgui_context)
	{
        vgui_context->m_Window = this;
        on_mouse_down_L([](WidgetBase* widget, WPARAM wp, LPARAM lp) -> LRESULT {
            // do a dynamic cast to see if the widget is a button type

            // if it's not a button type, early exit with 0

            // if it is a button type, call on_press()

            int x = LOWORD(lp);
            int y = HIWORD(lp);

            std::cout << x << ", " << y << '\n';

            return DefWindowProc(widget->handle(), WM_LBUTTONDOWN, wp, lp);
        });

	}
    LRESULT VWindow::on_event(UINT msg, WPARAM wp, LPARAM lp)
    {
        if (!m_vguiContext)
            return DefWindowProc(m_Handle, msg, wp, lp);


        // 1. Native events that MUST go to Windows
        switch (msg) {
            case WM_ERASEBKGND:
                return 1;
            case WM_NCHITTEST:
            case WM_ENTERSIZEMOVE:
            case WM_EXITSIZEMOVE:
            case WM_SIZING:
            case WM_WINDOWPOSCHANGING:
            case WM_SIZE:
                // notify vgui
                //m_vguiContext->on_event(handle(), msg, wp, lp);
                // but STILL let Windows finish the resize!
               // invalidate();
                m_vguiContext->on_event(handle(), msg, wp, lp);
                //redraw_now();

                return 0;
        }




        // 2. Painting
        if (msg == WM_PAINT)
        {

            PAINTSTRUCT ps;
            HDC hdc;
            begin_paint(ps, hdc);


            m_vguiContext->draw(hdc);

            end_paint(ps);
            return 0;
        }
        


        // 3. Forward normal events to VGUI widgets
        return m_vguiContext->on_event(handle(), msg, wp, lp);




    }




















































    /*
    LRESULT VWindow::old_on_event(UINT msg, WPARAM wParam, LPARAM lParam)
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
    }*/
}