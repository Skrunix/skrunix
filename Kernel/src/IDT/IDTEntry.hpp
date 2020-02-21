#pragma once

#include <stdint.h>

struct __attribute__((packed)) IDTEntry {
	uint16_t offsetLow;
	uint16_t selector;
	uint8_t  zero1;
	uint8_t  attributes;
	uint16_t offsetMid;
	uint32_t offsetHigh;
	uint32_t zero2;
};
static_assert(sizeof(IDTEntry) == 16);
