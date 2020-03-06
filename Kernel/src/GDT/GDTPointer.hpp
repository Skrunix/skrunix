#pragma once

#include "GDTEntry.hpp"

#include <Integers.hpp>

struct [[gnu::packed]] GDTPointer {
	UInt16    limit;
	GDTEntry* base;

	constexpr GDTPointer()
	    : limit()
	    , base(0) {}
};
static_assert(sizeof(GDTPointer) == 10);
