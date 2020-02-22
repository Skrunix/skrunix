#pragma once

#include "GDTEntry.hpp"

#include <integers>

struct __attribute__((packed)) GDTPointer {
	UInt16    limit;
	GDTEntry* base;

	constexpr GDTPointer()
	    : limit()
	    , base(0) {}
};
static_assert(sizeof(GDTPointer) == 10);
