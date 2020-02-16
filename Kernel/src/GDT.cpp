#include "GDT.hpp"

extern "C" {
typedef struct {
	uint16_t  limit;
	uintptr_t base;
} __attribute__((packed)) GDTPointer;
static_assert(sizeof(GDTPointer) == 10);

typedef struct {
	uint16_t limitLow;      // Limit 0:15
	uint16_t baseLow;       // Base 0:15
	uint8_t  baseMid;       // Base 16:23
	uint8_t  access;        // Access Byte
	uint8_t  limitHigh : 4; // Limit 16:19
	uint8_t  flags : 4;     // Flags
	uint8_t  baseHigh;      // Base 24:31
} __attribute__((packed)) GDTEntry;
static_assert(sizeof(GDTEntry) == 8);

extern void loadGDT(GDTPointer*);
}

GDTPointer gdt;
GDTEntry   gdtEntries[3];

GDT::GDT() {
	gdt.limit = sizeof(gdtEntries) - 1;
	gdt.base  = reinterpret_cast<uintptr_t>(&gdtEntries[0]);

	this->SetEntry(0, 0x1FFFF, 0, 0, 0);               // Null
	this->SetEntry(1, 0xFFFFF, 0, 0b10011010, 0b1010); // Code
	this->SetEntry(2, 0xFFFF, 0, 0b10010010, 0b0000);  // Data

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
