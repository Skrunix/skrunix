#pragma once

#include "GDTEntry.hpp"

#include <stdint.h>

struct __attribute__((packed)) GDTPointer {
	uint16_t  limit;
	GDTEntry* base;
};
static_assert(sizeof(GDTPointer) == 10);
