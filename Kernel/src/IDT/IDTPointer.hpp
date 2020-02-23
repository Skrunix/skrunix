#pragma once

#include "IDTEntry.hpp"

#include <integers>

struct [[gnu::packed]] IDTPointer {
	UInt16    limit;
	IDTEntry* offset;

	constexpr IDTPointer()
	    : limit()
	    , offset(0) {}
};
static_assert(sizeof(IDTPointer) == 10);
