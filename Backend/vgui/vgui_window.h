#pragma once
#include "../platform/win32/Application.h"
#include "../platform/win32/Window.h"
#include "../platform/win32/WidgetCallback.h"
#include "vgui_layerstack.h"


namespace vgui
{

	struct Context;


	// todo: add wrapper functions for the LayerStack, automatically add a background layer, stop widgets from being added to the background

	struct VWindow : native::Window
	{

		inline static bool registered = false;

		// Pointer to function that handles resizing
		void (*resize_interrupt_pfn)(VWindow&) = nullptr;
		native::Application* m_Owner = nullptr;
		Context* m_vguiContext = nullptr;
		LayerStack m_LayerStack;

		VWindow(native::Application* app);

		void begin_paint(PAINTSTRUCT& ps, HDC& hdc);

		void end_paint(PAINTSTRUCT& ps);

		LRESULT on_event(UINT msg, WPARAM wParam, LPARAM lParam) override;
		bool on_event(const Event& evt);
		//void init(HINSTANCE application, LPWSTR title, int x, int y, int w, int h);
	};
}
