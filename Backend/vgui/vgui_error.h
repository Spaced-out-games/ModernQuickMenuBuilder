#pragma once
#include <string>

namespace vgui
{

	// Defines the error code for JSON/file parsing errors
	enum class JSONError: int
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
	void exit(const std::string& error, JSONError code);
	void warn(const std::string& warning);


}