#pragma once
#include <string>
#include <array>
#include "thirdparty/entt/src/entt/core/hashed_string.hpp"

namespace vgui
{
	using string_hash_t = entt::id_type;


	string_hash_t hash(const std::string& string);




	using bounds_deserial_t = std::array<int, 4>;
	using action_deserial_t = std::array<std::string, 2>;
	static inline bool g_Debug = true;




}