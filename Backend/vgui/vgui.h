#pragma once
#include <string>
#include <array>

namespace vgui
{
	using bounds_deserial_t = std::array<int, 4>;
	using action_deserial_t = std::array<std::string, 2>;
	static inline bool g_Debug = true;
}