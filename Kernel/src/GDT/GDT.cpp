#include "GDT.hpp"
#include "GDTEntry.hpp"
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

GDTPointer gdt;
GDTEntry   gdtEntries[3];

GDT::GDT() {
	gdt.limit = sizeof(gdtEntries) - 1;
	gdt.base  = &gdtEntries[0];

	uint8_t access =
	    ACCESS_PRESENT | ACCESS_PRIV_KERNEL | ACCESS_GROW_UP | ACCESS_RW;
	uint8_t accessCode = access | ACCESS_TYPE_CODE;
	uint8_t accessData = access | ACCESS_TYPE_DATA;

	uint8_t flags     = FLAGS_GRANULARITY_4K;
	uint8_t flagsCode = flags | FLAGS_SIZE_64_CODE;
	uint8_t flagsData = flags | FLAGS_SIZE_64_DATA;

	this->SetEntry(0, UINT32_MAX, 0, 0, 0);                  // Null
	this->SetEntry(1, UINT32_MAX, 0, accessCode, flagsCode); // Code
	this->SetEntry(2, UINT32_MAX, 0, accessData, flagsData); // Data

	loadGDT(&gdt);
}

GDT::~GDT() {}

void GDT::SetEntry(uint8_t number, uint32_t limit, uintptr_t base,
                   uint8_t access, uint8_t flags) {
	gdtEntries[number].limitLow  = limit & 0xFFFF;
	gdtEntries[number].baseLow   = base & 0xFFFF;
	gdtEntries[number].baseMid   = (base >> 16) & 0xFF;
	gdtEntries[number].access    = access;
	gdtEntries[number].flags     = flags;
	gdtEntries[number].limitHigh = (limit >> 16) & 0x0F;
	gdtEntries[number].baseHigh  = (base >> 24) & 0xFF;
}
