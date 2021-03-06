#pragma once

#include "Attributes.hpp"
#include "IDTEntry.hpp"

#include <Integers/Integers.hpp>

struct PACKED alignas(2) IDTPointer {
	const UInt16    limit;
	const IDTEntry* offset;

	constexpr IDTPointer(const IDTEntry* start, const UInt16& count)
	    : limit(count * sizeof(IDTEntry))
	    , offset(start) {}
};
static_assert(sizeof(IDTPointer) == 10);
