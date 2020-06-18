#include "IDT.hpp"

#include "GDT/GDT.hpp"

#define ATTR_PRESENT (0b1 << 7)
#define ATTR_PRIV_ANY (0b00 << 5)
#define ATTR_TYPE_TASK (0b10101 << 0)
#define ATTR_TYPE_TRAP (0b01111 << 0)
#define ATTR_TYPE_INTERRUPT (0b01110 << 0)

extern "C" {
extern UIntPtr DefaultIntHandlers[];
extern void    flushIDT(IDTPointer*);
}

IDT::IDT(UIntPtr buffer)
    : entries(buffer.To<IDTEntry*>()) {
	IDTPointer idt(&this->entries[0], 256);

	UInt8 attributes = ATTR_PRESENT | ATTR_PRIV_ANY | ATTR_TYPE_INTERRUPT;
	for (UInt16 i = 0; i <= UINT8_MAX; ++i) {
		this->SetGate(i.low(), DefaultIntHandlers[static_cast<uint16_t>(i)],
		              GDT_CODE_SELECTOR, attributes);
	}
	flushIDT(&idt);
}

IDT::~IDT() {}

void IDT::SetGate(UInt8 number, UIntPtr offset, UInt16 selector,
                  UInt8 attributes) {
	this->entries[static_cast<uint8_t>(number)].offsetLow =
	    static_cast<uintptr_t>(offset) & 0xFFFF;
	this->entries[static_cast<uint8_t>(number)].selector   = selector;
	this->entries[static_cast<uint8_t>(number)].zero1      = 0;
	this->entries[static_cast<uint8_t>(number)].attributes = attributes;
	this->entries[static_cast<uint8_t>(number)].offsetMid =
	    (static_cast<uintptr_t>(offset) >> 16) & 0xFFFF;
	this->entries[static_cast<uint8_t>(number)].offsetHigh =
	    (static_cast<uintptr_t>(offset) >> 32) & 0xFFFFFFFF;
	this->entries[static_cast<uint8_t>(number)].zero2 = 0;
}
