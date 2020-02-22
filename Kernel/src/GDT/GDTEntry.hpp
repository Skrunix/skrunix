#pragma once

#include <integers>

struct __attribute__((packed)) GDTEntry {
	UInt16 limitLow; // Limit 0:15
	UInt16 baseLow;  // Base 0:15
	UInt8  baseMid;  // Base 16:23
	UInt8  access;   // Access Byte
	UInt8  flags;    // Flags (<<4) | Limit 16:19 (>>4)
	UInt8  baseHigh; // Base 24:31

	constexpr GDTEntry()
	    : limitLow()
	    , baseLow()
	    , baseMid()
	    , access()
	    , flags()
	    , baseHigh() {}
};
static_assert(sizeof(GDTEntry) == 8);
