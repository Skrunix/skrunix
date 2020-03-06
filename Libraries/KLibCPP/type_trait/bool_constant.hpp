#pragma once

#include <type_trait/integral_constant.hpp>

namespace std {

template <bool B>
using bool_constant = integral_constant<bool, B>;

using true_type  = bool_constant<true>;
using false_type = bool_constant<false>;

} // namespace std
