#include "vgui_error.h"
#include <iostream>



namespace vgui
{
	void exit(const std::string& error, Error code)
	{
		std::cerr << "[ERROR]: " << error;
		::exit(static_cast<int>(code));
	}
	void warn(const std::string& warning)
	{
		std::cerr << "[ERROR]: " << warning;
	}
}