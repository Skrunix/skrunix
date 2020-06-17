#pragma once

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

struct [[gnu::packed]] PageTableEntryFields {
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

	[[gnu::always_inline]] inline void SetPresent(Bool newValue) {
		this->value.fields._present = static_cast<bool>(newValue);
	}
	[[gnu::always_inline]] inline void SetWritable(Bool newValue) {
		this->value.fields._writable = static_cast<bool>(newValue);
	}
	[[gnu::always_inline]] inline void SetUserAccessible(Bool newValue) {
		this->value.fields._userAccessible = static_cast<bool>(newValue);
	}
	[[gnu::always_inline]] inline void SetWriteThroughCaching(Bool newValue) {
		this->value.fields._writeThroughCaching = static_cast<bool>(newValue);
	}
	[[gnu::always_inline]] inline void SetDisableCache(Bool newValue) {
		this->value.fields._disableCache = static_cast<bool>(newValue);
	}
	[[gnu::always_inline]] inline void SetAccessed(Bool newValue) {
		this->value.fields._accessed = static_cast<bool>(newValue);
	}
	[[gnu::always_inline]] inline void SetDirty(Bool newValue) {
		this->value.fields._dirty = static_cast<bool>(newValue);
	}
	[[gnu::always_inline]] inline void SetHugePage(Bool newValue) {
		this->value.fields._hugePage = static_cast<bool>(newValue);
	}
	[[gnu::always_inline]] inline void SetGlobal(Bool newValue) {
		this->value.fields._global = static_cast<bool>(newValue);
	}
	[[gnu::always_inline]] inline void SetUser1(UInt8 newValue) {
		this->value.fields._user1 = newValue.value;
	}
	[[gnu::always_inline]] inline void SetPhysicalAddress(UIntPtr newValue) {
		this->value.fields._physicalAddress = newValue.value >> PageShift;
	}
	[[gnu::always_inline]] inline void SetUser2(UInt16 newValue) {
		this->value.fields._user2 = newValue.value;
	}
	[[gnu::always_inline]] inline void SetNoExecute(Bool newValue) {
		this->value.fields._noExecute = static_cast<bool>(newValue);
	}

	[[gnu::always_inline]] inline Bool GetPresent() {
		return this->value.fields._present;
	}
	[[gnu::always_inline]] inline Bool GetWritable() {
		return this->value.fields._writable;
	}
	[[gnu::always_inline]] inline Bool GetUserAccessible() {
		return this->value.fields._userAccessible;
	}
	[[gnu::always_inline]] inline Bool GetWriteThroughCaching() {
		return this->value.fields._writeThroughCaching;
	}
	[[gnu::always_inline]] inline Bool GetDisableCache() {
		return this->value.fields._disableCache;
	}
	[[gnu::always_inline]] inline Bool GetAccessed() {
		return this->value.fields._accessed;
	}
	[[gnu::always_inline]] inline Bool GetDirty() {
		return this->value.fields._dirty;
	}
	[[gnu::always_inline]] inline Bool GetHugePage() {
		return this->value.fields._hugePage;
	}
	[[gnu::always_inline]] inline Bool GetGlobal() {
		return this->value.fields._global;
	}
	[[gnu::always_inline]] inline UInt8 GetUser1() {
		return this->value.fields._user1;
	}
	[[gnu::always_inline]] inline UIntPtr GetPhysicalAddress() {
		auto addr = this->value.fields._physicalAddress;
		if (addr & (1ull << 39)) {
			addr |= 0x000FFFF800000000;
		}
		return addr << PageShift;
	}
	[[gnu::always_inline]] inline UInt16 GetUser2() {
		return this->value.fields._user2;
	}
	[[gnu::always_inline]] inline Bool GetNoExecute() {
		return this->value.fields._noExecute;
	}
};
static_assert(sizeof(PageTableEntry) == 8);
static_assert(alignof(PageTableEntry) == 8);
