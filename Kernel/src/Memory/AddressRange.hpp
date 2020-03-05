#pragma once

#include <integers>

struct AddressRange {
	enum class Type : UInt32::BackingType {
		UNKNOWN          = 0,
		Usable           = 1,
		Reserved         = 2,
		ACPI_Reclaimable = 3,
		ACPI_NVS         = 4,
		Bad              = 5,
	};

	UIntPtr base;
	UInt64  length;
	Type    type;
	UInt32  extended;
};
static_assert(sizeof(AddressRange) == 24);
