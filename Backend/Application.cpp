#include "Application.h"

namespace QMB
{
	Application::Application()
	{

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