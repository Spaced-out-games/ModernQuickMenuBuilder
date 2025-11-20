#include "Window.h"


namespace QMB
{
    LRESULT Window::on_event(UINT msg, WPARAM wParam, LPARAM lParam)
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
        case WM_DROPFILES:
            if (m_onFileDrop) return m_onFileDrop(m_Handle, wParam, lParam);
            break;
        }


        // fallback to base class
        return WidgetBase::on_event(msg, wParam, lParam);
    }
    Window::Window(HWND handle)
    {
        m_Handle = handle;
    }

    void Window::init(
        HINSTANCE application,
        LPWSTR title,
        int x, int y, int w, int h,
        WindowCallback onClose,
        WindowCallback onPaint,
        WindowCallback onResize,
        WindowCallback onFileDrop

    )
    {
        m_onClose = onClose;
        m_onPaint = onPaint;
        m_onResize = onResize;
        m_onFileDrop = onFileDrop;
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