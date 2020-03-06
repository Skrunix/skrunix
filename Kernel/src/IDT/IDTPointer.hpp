#pragma once

#include "IDTEntry.hpp"

#include <Integers.hpp>

struct [[gnu::packed]] IDTPointer {
	UInt16    limit;
	IDTEntry* offset;

	constexpr IDTPointer()
	    : limit(256 * sizeof(IDTEntry))
	    , offset(0) {}
};
static_assert(sizeof(IDTPointer) == 10);
