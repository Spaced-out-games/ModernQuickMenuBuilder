#pragma once
#include <string>

namespace vgui
{

	enum class Error: int
	{
		SUCCESS_GENERIC,
		FAILURE_GENERIC,
		FILE_NOT_FOUND_ERROR,
		JSON_PARSE_ERROR,
		PAGE_NOT_FOUND_ERROR,
		INVALID_WIDGET_TYPE_ERROR,
		NO_IMPLEMENTATION_ERROR,
		INVALID_ACTION_FORMAT_ERROR

	};
	void exit(const std::string& error, Error code);
	void warn(const std::string& warning);


}