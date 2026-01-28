#include "vgui_window.h"
#include "vgui_event_win32_impl.h"


namespace vgui
{
	void VWindow::begin_paint(PAINTSTRUCT& ps, HDC& hdc)
	{
        hdc = BeginPaint(handle(), &ps);
	}
	void VWindow::end_paint(PAINTSTRUCT& ps)
	{
        EndPaint(handle(), &ps);

	}

	VWindow::VWindow(native::Application* app)
	{

        m_Owner = app;
        app->m_Window = this;

	}
    LRESULT VWindow::on_event(UINT msg, WPARAM wp, LPARAM lp)
    {
        // we interrupt active resize events and prevent their propagation
        if (msg == WM_SIZING) {
            if (!m_MaintainAspectRatio) return 0;
            RECT* r = (RECT*)lp;
            int w = r->right - r->left;
            int h = r->bottom - r->top;
            int new_w;
            int new_h;
            switch (wp) {
                case WMSZ_LEFT:
                    new_h = (int)(w / m_Aspect_ratio);
                    r->top = r->bottom - new_h;
                    break;
                case WMSZ_RIGHT:
                    new_h = (int)(w / m_Aspect_ratio);
                    r->bottom = r->top + new_h;
                    break;
                case WMSZ_TOP:
                    new_w = (int)(h * m_Aspect_ratio);
                    r->left = r->right - new_w;
                    break;
                case WMSZ_BOTTOM:
                    new_w = (int)(h * m_Aspect_ratio);
                    r->right = r->left + new_w;
                    break;
                default:
                    // get new width and height so that they respect the aspect ratio
                    // in terms of the current height
                    // compare these versus the old dimensions. Whichever axis
                    // isn't dominant gets updated
                    break;

            }
            return 0;
        }


        



        // we take the event, convert it, and add it to the queue
        vgui::Event evt;
        vgui::vgui_event_win32_impl(m_Owner, evt, msg, wp, lp);
        if (evt.type == EventType::LIFETIME_NULL_EVENT) return 0;
        
        
        m_LayerStack.on_event(evt);
        return 0;
    }

    /*
    void VWindow::init(HINSTANCE application, LPWSTR title, int x, int y, int w, int h)
    {
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
            (HBRUSH)(0) // default background
        );
    }*/

    bool VWindow::on_event(const Event& evt)
    {

        if (m_LayerStack.size() == 0) return 0;

        //if (!m_vguiContext)
        //    return 0;


        // 1. Native events that MUST go to Windows
        switch (evt.type) {
            case EventType::WINDOW_ERASE_BG_EVENT:
                return 1;
            //case WM_NCHITTEST:
            case EventType::WINDOW_BEGIN_MOVE_RESIZE_EVENT:
            case EventType::WINDOW_END_MOVE_RESIZE_EVENT:
            case EventType::WINDOW_RESIZING_EVENT:
            case EventType::WINDOW_STATE_CHANGING_EVENT:
            case EventType::WINDOW_RESIZE_EVENT:

                return 0;
        }




        // 2. Painting
        if (evt.type == EventType::WINDOW_PAINT_EVENT)
        {

            PAINTSTRUCT ps;
            HDC hdc;
            begin_paint(ps, hdc);

            // a little hack, for now
            m_LayerStack.draw(evt);

            //m_vguiContext->draw(hdc);

            end_paint(ps);
        }
        


        // 3. Forward normal events to VGUI widgets
        return 0;




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