#include "IDT.hpp"

extern "C" {
typedef struct {
	uint16_t limit;
	uint64_t offset;
} __attribute__((packed)) IDTR;

typedef struct {
	uint16_t offsetLow;
	uint16_t selector;
	uint8_t  zero1;
	uint8_t  attributes;
	uint16_t offsetMid;
	uint32_t offsetHigh;
	uint32_t zero2;
} __attribute__((packed)) IDTDescriptor;

extern uintptr_t DefaultIntHandlers[];
extern void      flushIDT(IDTR*);
}

static IDTR          idtr;
static IDTDescriptor descriptors[256];

IDT::IDT() {
	idtr.limit  = sizeof(IDTDescriptor) * 256 - 1;
	idtr.offset = reinterpret_cast<uintptr_t>(&descriptors);

	this->SetGate(0, DefaultIntHandlers[0], 0x18, 0x8E);
	for (uint8_t i = 1; i > 0; ++i) {
		this->SetGate(i, DefaultIntHandlers[i], 0x08, 0x8E);
	}
	flushIDT(&idtr);
}

IDT::~IDT() {}

void IDT::SetGate(uint8_t number, uintptr_t offset, uint16_t selector,
                  uint8_t attributes) {
	descriptors[number].offsetLow  = offset & 0xFFFF;
	descriptors[number].selector   = selector;
	descriptors[number].zero1      = 0;
	descriptors[number].attributes = attributes;
	descriptors[number].offsetMid  = (offset >> 16) & 0xFFFF;
	descriptors[number].offsetHigh =
	    static_cast<uint32_t>(offset >> 32) & 0xFFFFFFFF;
	descriptors[number].zero2 = 0;
}
