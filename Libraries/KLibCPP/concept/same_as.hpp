#pragma once

#include <type_trait/is_same.hpp>

namespace std {

template <class T, class U>
concept same_as = std::is_same_v<T, U>;

} // namespace std
