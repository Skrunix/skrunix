#pragma once

#define const_inline [[gnu::always_inline]] inline constexpr

#include <Integers/types/unsigned/UInt.hpp>
#include <Integers/types/unsigned/UInt16.hpp>
#include <Integers/types/unsigned/UInt32.hpp>
#include <Integers/types/unsigned/UInt64.hpp>
#include <Integers/types/unsigned/UInt8.hpp>
#include <Integers/types/unsigned/UIntPtr.hpp>
#include <Integers/types/unsigned/USize.hpp>

#undef const_inline
