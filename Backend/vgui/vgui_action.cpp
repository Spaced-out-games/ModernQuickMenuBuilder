#include "vgui_action.h"
#include "../platform/win32/Application.h"
namespace vgui
{
	void Action::run(native::Application* app) {
		if (m_Type == ActionType::EXIT)
		{
			#ifdef _DEBUG
				if (app) app->exit("Closing application via action...");
			#else
				if (app) app->exit(""); // Make sure to swap for json["message"]
			#endif
		}
	}


}

// vwindow