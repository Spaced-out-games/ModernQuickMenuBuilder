#include "hash.h"
namespace qmb {

    string_hash_t hash(const std::string& string)
    {
        return entt::hashed_string{ string.c_str() }.value();
    }

}