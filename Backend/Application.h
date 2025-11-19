#pragma once
#include <windows.h>
#include <cassert>

namespace QMB
{
	struct Application
	{
		HINSTANCE m_Application = nullptr;


		// Default constructor
		Application();
		~Application() = default;


		// Initializes the application
		void init();


		// Returns true if the Application is valid
		operator bool() const;
		operator HINSTANCE() const;

		//virtual void on_init() = 0;

	};
}