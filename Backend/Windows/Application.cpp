#include "Application.h"

namespace Windows
{
	Application::Application()
	{

	}

	int Application::run()
	{
		MSG msg;
		while (GetMessage(&msg, nullptr, 0, 0)) { // bp
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		return 0;
	}

	void Application::init()
	{
		if (m_Application == nullptr)
			m_Application = GetModuleHandle(nullptr);

		// If it fails, we know why.
		assert(m_Application != nullptr);
	}

	Application::operator bool() const
	{
		return m_Application != nullptr;
	}

	Application::operator HINSTANCE() const
	{
		return m_Application;
	}

}