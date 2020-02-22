#pragma once

#include <stdint.h>

struct __attribute__((packed)) UIntPtr {
	using BackingType = uintptr_t;

	BackingType value;

	constexpr static const BackingType min = INT64_MIN;
	constexpr static const BackingType max = INT64_MAX;

	constexpr UIntPtr()
	    : value(0) {}
	constexpr UIntPtr(BackingType value)
	    : value(value) {}

	inline UIntPtr operator&(UIntPtr rhs) { return value & rhs.value; };

	inline UIntPtr operator>>(UIntPtr rhs) { return value >> rhs.value; };
};
static_assert(sizeof(UIntPtr) == 8);
