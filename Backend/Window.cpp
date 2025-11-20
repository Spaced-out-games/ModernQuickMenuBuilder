#include "Window.h"


namespace Windows
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
            (HBRUSH)(COLOR_WINDOW + 1) // default background
        );
        DragAcceptFiles(m_Handle, TRUE);

    }
}