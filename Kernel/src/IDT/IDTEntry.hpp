#pragma once

#include <integers>

struct __attribute__((packed)) IDTEntry {
	UInt16 offsetLow;
	UInt16 selector;
	UInt8  zero1;
	UInt8  attributes;
	UInt16 offsetMid;
	UInt32 offsetHigh;
	UInt32 zero2;

	constexpr IDTEntry()
	    : offsetLow()
	    , selector()
	    , zero1(0)
	    , attributes()
	    , offsetMid()
	    , offsetHigh()
	    , zero2(0) {}
};
static_assert(sizeof(IDTEntry) == 16);
