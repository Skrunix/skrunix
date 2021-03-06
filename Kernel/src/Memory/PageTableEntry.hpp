#pragma once

#include "Attributes.hpp"
#include "PageAlloc.hpp"

#include <Boolean/Boolean.hpp>
#include <Integers/Integers.hpp>

#define PRESENT 1ull << 0
#define WRITABLE 1ull << 1
#define USERACCESS 1ull << 2
#define NOWRITECACHE 1ull << 3
#define NOCACHE 1ull << 4
#define ACCESSED 1ull << 5
#define DIRTY 1ull << 6
#define HUGEPAGE 1ull << 7
#define GLOBAL 1ull << 8
#define NOEXEC 1ull << 63

struct PACKED PageTableEntryFields {
	bool     _present : 1;
	bool     _writable : 1;
	bool     _userAccessible : 1;
	bool     _writeThroughCaching : 1;
	bool     _disableCache : 1;
	bool     _accessed : 1;
	bool     _dirty : 1;
	bool     _hugePage : 1;
	bool     _global : 1;
	uint8_t  _user1 : 3;
	uint64_t _physicalAddress : 40;
	uint16_t _user2 : 11;
	bool     _noExecute : 1;
};
static_assert(sizeof(PageTableEntryFields) == 8);

union PageTableEntryValue {
	UInt64               value;
	PageTableEntryFields fields;

	constexpr PageTableEntryValue(UInt64 bitValue)
	    : value(bitValue) {}
};
static_assert(sizeof(PageTableEntryValue::value) ==
              sizeof(PageTableEntryValue::fields));

struct PageTableEntry {
	PageTableEntryValue value;

	constexpr PageTableEntry(UInt64 bitValue)
	    : value(bitValue) {}

	ALWAY_INLINE void SetPresent(Bool newValue) {
		this->value.fields._present = static_cast<bool>(newValue);
	}
	ALWAY_INLINE void SetWritable(Bool newValue) {
		this->value.fields._writable = static_cast<bool>(newValue);
	}
	ALWAY_INLINE void SetUserAccessible(Bool newValue) {
		this->value.fields._userAccessible = static_cast<bool>(newValue);
	}
	ALWAY_INLINE void SetWriteThroughCaching(Bool newValue) {
		this->value.fields._writeThroughCaching = static_cast<bool>(newValue);
	}
	ALWAY_INLINE void SetDisableCache(Bool newValue) {
		this->value.fields._disableCache = static_cast<bool>(newValue);
	}
	ALWAY_INLINE void SetAccessed(Bool newValue) {
		this->value.fields._accessed = static_cast<bool>(newValue);
	}
	ALWAY_INLINE void SetDirty(Bool newValue) {
		this->value.fields._dirty = static_cast<bool>(newValue);
	}
	ALWAY_INLINE void SetHugePage(Bool newValue) {
		this->value.fields._hugePage = static_cast<bool>(newValue);
	}
	ALWAY_INLINE void SetGlobal(Bool newValue) {
		this->value.fields._global = static_cast<bool>(newValue);
	}
	ALWAY_INLINE void SetUser1(UInt8 newValue) {
		this->value.fields._user1 = static_cast<uint8_t>(newValue);
	}
	ALWAY_INLINE void SetPhysicalAddress(UIntPtr newValue) {
		this->value.fields._physicalAddress =
		    static_cast<uintptr_t>(newValue) >> PageShift;
	}
	ALWAY_INLINE void SetUser2(UInt16 newValue) {
		this->value.fields._user2 = static_cast<uint16_t>(newValue);
	}
	ALWAY_INLINE void SetNoExecute(Bool newValue) {
		this->value.fields._noExecute = static_cast<bool>(newValue);
	}

	ALWAY_INLINE Bool GetPresent() { return this->value.fields._present; }
	ALWAY_INLINE Bool GetWritable() { return this->value.fields._writable; }
	ALWAY_INLINE Bool GetUserAccessible() {
		return this->value.fields._userAccessible;
	}
	ALWAY_INLINE Bool GetWriteThroughCaching() {
		return this->value.fields._writeThroughCaching;
	}
	ALWAY_INLINE Bool GetDisableCache() {
		return this->value.fields._disableCache;
	}
	ALWAY_INLINE Bool    GetAccessed() { return this->value.fields._accessed; }
	ALWAY_INLINE Bool    GetDirty() { return this->value.fields._dirty; }
	ALWAY_INLINE Bool    GetHugePage() { return this->value.fields._hugePage; }
	ALWAY_INLINE Bool    GetGlobal() { return this->value.fields._global; }
	ALWAY_INLINE UInt8   GetUser1() { return this->value.fields._user1; }
	ALWAY_INLINE UIntPtr GetPhysicalAddress() {
		auto addr = this->value.fields._physicalAddress;
		if (addr & (1ull << 39)) {
			addr |= 0x000FFFF800000000;
		}
		return addr << PageShift;
	}
	ALWAY_INLINE UInt16 GetUser2() { return this->value.fields._user2; }
	ALWAY_INLINE Bool   GetNoExecute() { return this->value.fields._noExecute; }
};
static_assert(sizeof(PageTableEntry) == 8);
static_assert(alignof(PageTableEntry) == 8);
