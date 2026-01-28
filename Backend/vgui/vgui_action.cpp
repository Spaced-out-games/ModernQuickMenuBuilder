#include "vgui_action.h"
#include "../platform/win32/Application.h"
namespace vgui
{
	void Action::run(native::Application* app) {
		if (m_Type == ActionType::EXIT)
		{
			action::exit(app, "");
		}
	}

	namespace action
	{
		void exit(native::Application* app, const std::string& msg) {
			// garbage collection
			app->exit(msg);
		}
	}
}

// vwindow