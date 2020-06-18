#pragma once

#include <Integers/Integers.hpp>

struct AddressRange {
	enum class Type : uint32_t {
		UNKNOWN          = 0,
		Usable           = 1,
		Reserved         = 2,
		ACPI_Reclaimable = 3,
		ACPI_NVS         = 4,
		Bad              = 5,
	};

	UIntPtr base;
	USize   length;
	Type    type;
	UInt32  extended;
};
static_assert(sizeof(AddressRange) == 24);
