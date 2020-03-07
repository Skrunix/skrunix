#pragma once

#include "GDTEntry.hpp"

#include <Integers/Integers.hpp>

struct [[gnu::packed]] GDTPointer {
	const UInt16    limit;
	const GDTEntry* base;

	constexpr GDTPointer(const GDTEntry* start, const UInt16& count)
	    : limit(count)
	    , base(start) {}
};
static_assert(sizeof(GDTPointer) == 10);
