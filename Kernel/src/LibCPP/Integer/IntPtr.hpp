#pragma once

#include <stdint.h>

struct [[gnu::packed]] IntPtr {
	using BackingType = intptr_t;

	BackingType value;

	constexpr static const BackingType min = INT64_MIN;
	constexpr static const BackingType max = INT64_MAX;

	constexpr IntPtr()
	    : value(0) {}
	constexpr IntPtr(BackingType value)
	    : value(value) {}
};
static_assert(sizeof(IntPtr) == 8);
