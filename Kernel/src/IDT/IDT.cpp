#include "IDT.hpp"

#include "GDT/GDT.hpp"
#include "IDTEntry.hpp"
#include "IDTPointer.hpp"

#define ATTR_PRESENT (0b1 << 7)
#define ATTR_PRIV_ANY (0b00 << 5)
#define ATTR_TYPE_TASK (0b10101 << 0)
#define ATTR_TYPE_TRAP (0b01111 << 0)
#define ATTR_TYPE_INTERRUPT (0b01110 << 0)

extern "C" {
extern uintptr_t DefaultIntHandlers[];
extern void      flushIDT(IDTPointer*);
}

static IDTPointer idt;
static IDTEntry   idtEntries[256];

IDT::IDT() {
	idt.limit  = sizeof(idtEntries) - 1;
	idt.offset = &idtEntries[0];

	uint8_t attributes = ATTR_PRESENT | ATTR_PRIV_ANY | ATTR_TYPE_INTERRUPT;
	for (uint16_t i = 0; i <= UINT8_MAX; ++i) {
		this->SetGate(i, DefaultIntHandlers[i], GDT_CODE_SELECTOR, attributes);
	}
	flushIDT(&idt);
}

IDT::~IDT() {}

void IDT::SetGate(uint8_t number, uintptr_t offset, uint16_t selector,
                  uint8_t attributes) {
	idtEntries[number].offsetLow  = offset & 0xFFFF;
	idtEntries[number].selector   = selector;
	idtEntries[number].zero1      = 0;
	idtEntries[number].attributes = attributes;
	idtEntries[number].offsetMid  = (offset >> 16) & 0xFFFF;
	idtEntries[number].offsetHigh = (offset >> 32) & 0xFFFFFFFF;
	idtEntries[number].zero2      = 0;
}
