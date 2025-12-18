#pragma once
#include "vgui.h"

namespace vgui
{
	string_hash_t hash(const std::string& string)
	{
		return entt::hashed_string{ string.c_str() }.value();
	}
}