#pragma once

#include <stdint.h>

struct __attribute__((packed)) GDTEntry {
	uint16_t limitLow;      // Limit 0:15
	uint16_t baseLow;       // Base 0:15
	uint8_t  baseMid;       // Base 16:23
	uint8_t  access;        // Access Byte
	uint8_t  limitHigh : 4; // Limit 16:19
	uint8_t  flags : 4;     // Flags
	uint8_t  baseHigh;      // Base 24:31
};
static_assert(sizeof(GDTEntry) == 8);
