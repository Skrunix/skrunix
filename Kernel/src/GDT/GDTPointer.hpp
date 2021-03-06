#pragma once

#include "Attributes.hpp"
#include "GDTEntry.hpp"

#include <Integers/Integers.hpp>

struct PACKED alignas(2) GDTPointer {
	const UInt16    limit;
	const GDTEntry* base;

	constexpr GDTPointer(const GDTEntry* start, const UInt16& count)
	    : limit(count)
	    , base(start) {}
};
static_assert(sizeof(GDTPointer) == 10);
