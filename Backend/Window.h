#pragma once
#include "WidgetBase.h"
#include "Image.h"
#include "WidgetCallback.h"

namespace Windows
{

    class Window : public WidgetBase
    {
        // Useful for auto-registering the class
        inline static bool registered = false;
        




    protected:

    public:
        // For testing purposes. Use something better, dumbass.
        Image img = {}; 


        // DONT FORGET TO CALL INIT() AFTER THIS!!!!
        Window() = default;

        // construct from an existing handle.
        // For use when the application entry point
        // changes in a full release.
        Window(HWND handle);


        // initializes the window
        void init(HINSTANCE application, LPWSTR title, int x, int y, int w, int h);
    };
}
