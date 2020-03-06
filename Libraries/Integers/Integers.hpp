#pragma once

#define const_inline [[gnu::always_inline]] inline constexpr

#include "types/unsigned/UInt.hpp"
#include "types/unsigned/UInt16.hpp"
#include "types/unsigned/UInt32.hpp"
#include "types/unsigned/UInt64.hpp"
#include "types/unsigned/UInt8.hpp"
#include "types/unsigned/UIntPtr.hpp"
#include "types/unsigned/USize.hpp"

#undef const_inline
