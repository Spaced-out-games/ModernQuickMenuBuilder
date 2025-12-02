#pragma once
#include <Windows.h>
#include <iostream>
#include "WidgetCallback.h"

namespace native
{



    
    ///
    /// Gives control back to the widget
    ///
    LRESULT CALLBACK EventDelegate(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);



	/// 
	/// Basic widget type. Stores a callback table and a HWND, and delegates control
    /// to those callbacks
	/// 
	class WidgetBase
	{

        

        protected:

            // Windows `window` handle
            HWND m_Handle = nullptr;

            // Callback table
            WidgetCallbacks m_Callbacks = {};

            // Low-level handle initialization
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
            ///                   constructor                   ///
            ///                                                 ///
            

            // DONT FORGET TO CALL INIT() AFTER THIS!!!!
            WidgetBase() = default;

            ///                                                 ///
            ///                    destructor                   ///
            ///                                                 ///
            ~WidgetBase() = default;




            
            // EventDelegate calls this, and this calls the callback table
            virtual LRESULT on_event(UINT msg, WPARAM wParam, LPARAM lParam);

            ///                                                 ///
            ///                     getters                     ///
            ///                                                 ///
            ///
                        // Checks if the widget is valid
            operator bool() const
            {
                return m_Handle;
            }

            // Gets widget's native handle
            operator HWND() const
            {
                return m_Handle;
            }

            // Gets the widget's bounding box
            RECT bounds() const;

            HWND handle() const;

            
            

           ///                                                 ///
           ///                     actions                     ///
           ///                                                 ///
           
            
            // Sets the event hook
           
            // Shows the widget
            void show() const;

            // Hides the widget
            void hide() const;

            // Enables the widget
            void enable() const;

            // Disables the widget
            void disable() const;

            // Resizes the widget
            void resize(int new_width, int new_height) const;

            // Moves the widget
            void move(int new_X, int new_Y) const;

            // Moves the widget to the front
            void move_forward() const;

            // Moves the widget back
            void move_backward() const;

            // Gets the text contents of the widget
            std::string text() const;

            // Sets the text contents of the widget
            void text(const std::string& text) const;

            // Invalidates the draw state of the widget
            void invalidate() const;

            // Forces this widget to draw immediately
            void redraw_now() const;

            // Focuses this widget
            void focus(bool) const;

            // Returns true of this widget is focused
            bool focus() const;

            // Tells this widget to capture input
            void capture() const;

            // Tells this widget to release input
            void release() const;


	};

    

}