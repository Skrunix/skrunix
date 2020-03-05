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

IDT::IDT(void* buffer)
    : idt()
    , entries(reinterpret_cast<IDTEntry*>(buffer)) {
	this->idt.offset = &this->entries[0];

	UInt8 attributes = ATTR_PRESENT | ATTR_PRIV_ANY | ATTR_TYPE_INTERRUPT;
	for (UInt16 i = 0; i <= UINT8_MAX; ++i) {
		this->SetGate(i.low(), DefaultIntHandlers[i.value], GDT_CODE_SELECTOR,
		              attributes);
	}
	flushIDT(&this->idt);
}

IDT::~IDT() {}

void IDT::SetGate(UInt8 number, UIntPtr offset, UInt16 selector,
                  UInt8 attributes) {
	this->entries[number.value].offsetLow  = offset.value & 0xFFFF;
	this->entries[number.value].selector   = selector;
	this->entries[number.value].zero1      = 0;
	this->entries[number.value].attributes = attributes;
	this->entries[number.value].offsetMid  = (offset.value >> 16) & 0xFFFF;
	this->entries[number.value].offsetHigh = (offset.value >> 32) & 0xFFFFFFFF;
	this->entries[number.value].zero2      = 0;
}
