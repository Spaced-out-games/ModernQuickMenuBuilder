#pragma once
#include "thirdparty/entt/src/entt/core/hashed_string.hpp"
#include <string>

namespace qmb {

    using string_hash_t = entt::id_type;
    using index_t = uint32_t;
    static constexpr index_t NULL_INDEX = UINT32_MAX;
    string_hash_t hash(const std::string& string);

}