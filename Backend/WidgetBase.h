#pragma once
#include <Windows.h>
#include <iostream>


namespace QMB
{
    LRESULT CALLBACK EventDelegate(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

    

	class WidgetBase
	{

        

        protected:
        HWND m_Handle = nullptr;

        void init_impl(
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
        );

        public:
            WidgetBase() = default;

            operator bool() const;

            operator HWND() const;

            
            virtual LRESULT on_event(UINT msg, WPARAM wParam, LPARAM lParam) 
            {
                return 0;
            };

	};


    /*
    switch (msg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);  // close the message loop
        return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        TextOutA(hdc, 10, 10, "Hello WinAPI!", 13);
        EndPaint(hwnd, &ps);
    }
    return 0;
    }
    */

    

}