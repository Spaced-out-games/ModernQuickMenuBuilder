#include "Window.h"


namespace native
{
    
    Window::Window(HWND handle)
    {
        m_Handle = handle;
    }

    void Window::init(
        HINSTANCE application,
        LPWSTR title,
        int x, int y, int w, int h)
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
        DragAcceptFiles(m_Handle, TRUE);

    }

    void Window::enable_drag_drop()
    {
        DragAcceptFiles(m_Handle , TRUE);
    }

    void Window::ToggleFullscreen()
    {
        // Use GetWindowLongPtr/SetWindowLongPtr for 64-bit compatibility
        LONG_PTR style = GetWindowLongPtr(m_Handle, GWL_STYLE);
        LONG_PTR exStyle = GetWindowLongPtr(m_Handle, GWL_EXSTYLE);

        if (!isFullscreen)
        {
            // Save current state
            GetWindowPlacement(m_Handle, &wpPrev);
            prevStyle = style;
            prevExStyle = exStyle;

            // Remove window chrome (titlebar, borders)
            SetWindowLongPtr(m_Handle, GWL_STYLE, style & ~WS_OVERLAPPEDWINDOW);
            SetWindowLongPtr(m_Handle, GWL_EXSTYLE, exStyle & ~(WS_EX_DLGMODALFRAME | WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE));

            // Get monitor rect containing the window
            HMONITOR hMon = MonitorFromWindow(m_Handle, MONITOR_DEFAULTTONEAREST);
            MONITORINFO mi = {}; mi.cbSize = sizeof(mi);
            GetMonitorInfo(hMon, &mi);

            // Set to topmost and cover the whole monitor. Use rcMonitor for full monitor, rcWork to keep taskbar visible.
            SetWindowPos(m_Handle, HWND_TOPMOST,
                mi.rcMonitor.left, mi.rcMonitor.top,
                mi.rcMonitor.right - mi.rcMonitor.left,
                mi.rcMonitor.bottom - mi.rcMonitor.top,
                SWP_NOOWNERZORDER | SWP_FRAMECHANGED | SWP_SHOWWINDOW);

            isFullscreen = true;
        }
        else
        {
            // Restore styles
            SetWindowLongPtr(m_Handle, GWL_STYLE, prevStyle);
            SetWindowLongPtr(m_Handle, GWL_EXSTYLE, prevExStyle);

            // Restore previous placement (position, size, showCmd)
            SetWindowPlacement(m_Handle, &wpPrev);

            // Ensure it's no longer topmost and force frame recalculation
            SetWindowPos(m_Handle, HWND_NOTOPMOST,
                0, 0, 0, 0,
                SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER |
                SWP_NOOWNERZORDER | SWP_FRAMECHANGED | SWP_SHOWWINDOW);

            isFullscreen = false;
        }
    }

}