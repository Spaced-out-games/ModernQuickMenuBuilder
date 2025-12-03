#pragma once
#include "../native/Window.h"
#include "../native/WidgetCallback.h"



namespace vgui
{

	struct Context;


	struct VWindow : native::Window, native::IWidgetCallbacks
	{
		Context* m_vguiContext = nullptr;

		VWindow(vgui::Context* vgui_context);

		void begin_paint(PAINTSTRUCT& ps, HDC& hdc);

		void end_paint(PAINTSTRUCT& ps);

		LRESULT on_event(UINT msg, WPARAM wParam, LPARAM lParam) override;

	};
}
