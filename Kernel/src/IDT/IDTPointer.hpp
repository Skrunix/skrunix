#pragma once

#include "IDTEntry.hpp"
#include <stdint.h>

struct __attribute__((packed)) IDTPointer {
	uint16_t  limit;
	IDTEntry* offset;
};
static_assert(sizeof(IDTPointer) == 10);
