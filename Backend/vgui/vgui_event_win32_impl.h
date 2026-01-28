#pragma once
#include "../platform/win32/Application.h"
#include "../platform/win32/Window.h"
#include "vgui_event.h"
#include <windowsx.h>
#include <windows.h>
namespace vgui
{


    // handles DEFAULT windows events; anything else is engine-level!
    bool vgui_event_win32_impl(native::Application* app, vgui::Event& evt, const MSG& msg);

    bool vgui_event_win32_impl(native::Application* app, vgui::Event& evt, UINT msg, WPARAM wp, LPARAM lp);



    bool PollEvent(native::Application* app, vgui::Event& evt, bool dispatch_native);

    


}