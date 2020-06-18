#include "GDT.hpp"

#include "GDTPointer.hpp"

#define ACCESS_PRESENT (0b1 << 7)
#define ACCESS_PRIV_KERNEL (0b00 << 5)
#define ACCESS_TYPE_CODE (0b11 << 3)
#define ACCESS_TYPE_DATA (0b10 << 3)
#define ACCESS_GROW_UP (0b0 << 2)
#define ACCESS_RW (0b1 << 1)

#define FLAGS_GRANULARITY_4K (0b1 << 3)
#define FLAGS_SIZE_64_CODE (0b01 << 1)
#define FLAGS_SIZE_64_DATA (0b00 << 1)

extern "C" {
extern void loadGDT(GDTPointer*);
}

GDT::GDT() {
	GDTPointer gdt(&this->gdtEntries[0], sizeof(this->gdtEntries) - 1);

	UInt8 access =
	    ACCESS_PRESENT | ACCESS_PRIV_KERNEL | ACCESS_GROW_UP | ACCESS_RW;
	UInt8 accessCode = access | ACCESS_TYPE_CODE;
	UInt8 accessData = access | ACCESS_TYPE_DATA;

	UInt8 flags     = FLAGS_GRANULARITY_4K;
	UInt8 flagsCode = flags | FLAGS_SIZE_64_CODE;
	UInt8 flagsData = flags | FLAGS_SIZE_64_DATA;

	this->SetEntry(0, -1, 0, 0, 0);                  // Null
	this->SetEntry(1, -1, 0, accessCode, flagsCode); // Code
	this->SetEntry(2, -1, 0, accessData, flagsData); // Data

	loadGDT(&gdt);
}

GDT::~GDT() {}

void GDT::SetEntry(UInt8 number, UInt32 limit, UIntPtr base, UInt8 access,
                   UInt8 flags) {
	this->gdtEntries[static_cast<uint8_t>(number)].limitLow = limit.low();
	this->gdtEntries[static_cast<uint8_t>(number)].baseLow =
	    static_cast<uintptr_t>(base) & 0xFFFF;
	this->gdtEntries[static_cast<uint8_t>(number)].baseMid =
	    (static_cast<uintptr_t>(base) >> 16) & 0xFF;
	this->gdtEntries[static_cast<uint8_t>(number)].access = access;
	this->gdtEntries[static_cast<uint8_t>(number)].flags =
	    (static_cast<uint8_t>(flags) << 4) |
	    ((static_cast<uint32_t>(limit) >> 16) & 0x0F);
	this->gdtEntries[static_cast<uint8_t>(number)].baseHigh =
	    (static_cast<uintptr_t>(base) >> 24) & 0xFF;
}
