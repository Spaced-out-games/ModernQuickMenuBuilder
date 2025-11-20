#pragma once
#include <Windows.h>
#include <iostream>
#include "WidgetCallback.h"

namespace QMB
{



    // todo: take in a WidgetBase instead of a HWND
    //using callback_t = LRESULT(*)(HWND, WPARAM, LPARAM);


    LRESULT CALLBACK EventDelegate(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);




	class WidgetBase
	{

        

        protected:
            HWND m_Handle = nullptr;
            WidgetCallbacks m_Callbacks = {};


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


            ///                                                 ///
            ///                  constructors                   ///
            ///                                                 ///
            WidgetBase() = default;

            ///                                                 ///
            ///                   destructors                   ///
            ///                                                 ///
            ~WidgetBase() = default;




            
            // Center brain. Calls everything else
            virtual LRESULT on_event(UINT msg, WPARAM wParam, LPARAM lParam);

            ///                                                 ///
            ///                     getters                     ///
            ///                                                 ///
            /// 
            inline event_pfn_t on_file_drop();

            inline paint_pfn_t on_paint();
            inline mouse_pfn_t on_mouse_enter();
            inline mouse_pfn_t on_mouse_exit();
            inline mouse_pfn_t on_mouse_move();
            inline mouse_pfn_t on_mouse_down_L();
            inline mouse_pfn_t on_mouse_up_L();
            inline mouse_pfn_t on_mouse_down_R();
            inline mouse_pfn_t on_mouse_up_R();

            inline event_pfn_t on_resize();
            inline event_pfn_t on_context_menu();
            inline event_pfn_t on_focus();
            inline event_pfn_t on_unfocus();
            inline event_pfn_t on_key_down();
            inline event_pfn_t on_key_up();
            inline event_pfn_t on_char();
            inline event_pfn_t on_construct();
            inline event_pfn_t on_destruct();
            void begin_paint(PAINTSTRUCT&, HDC&);
            void        end_paint(PAINTSTRUCT&);

            operator bool() const
            {
                return m_Handle;
            }

            operator HWND() const
            {
                return m_Handle;
            }
            RECT bounds() const;


            ///                                                 ///
            ///                     setters                     ///
            ///                                                 ///
            
            void on_paint(paint_pfn_t);
            void on_mouse_enter(mouse_pfn_t);
            void on_mouse_exit(mouse_pfn_t);
            void on_mouse_move(mouse_pfn_t);
            void on_mouse_down_L(mouse_pfn_t);
            void on_mouse_up_L(mouse_pfn_t);
            void on_mouse_down_R(mouse_pfn_t);
            void on_mouse_up_R(mouse_pfn_t);

            void on_file_drop(event_pfn_t);
            void on_resize(event_pfn_t);
            void on_context_menu(event_pfn_t);
            void on_focus(event_pfn_t);
            void on_unfocus(event_pfn_t);
            void on_key_down(event_pfn_t);
            void on_key_up(event_pfn_t);
            void on_char(event_pfn_t);
            void on_construct(event_pfn_t);
            void on_destruct(event_pfn_t);
            
           ///                                                 ///
           ///                     actions                     ///
           ///                                                 ///
           inline void show() const;
           inline void hide() const;
           inline void enable() const;
           inline void disable() const;
           inline void resize(int new_width, int new_height) const;
           inline void move(int new_X, int new_Y) const;
           inline void move_forward() const;
           inline void move_backward() const;
           inline std::string text() const;
           inline void text(const std::string& text) const;
           inline void invalidate() const;
           inline void redraw_now() const;
           inline void focus(bool) const;
           inline bool focus() const;
           inline void capture() const;
           inline void release() const;


	};

    

}