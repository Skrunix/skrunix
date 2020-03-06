#pragma once

#include "IDTEntry.hpp"
#include "IDTPointer.hpp"

#include <Integers.hpp>

class IDT {
  public:
	IDT(void* buffer);
	IDT(const IDT&) = delete;
	~IDT();

	IDT& operator=(const IDT&) = delete;

  private:
	void SetGate(UInt8 number, UIntPtr offset, UInt16 selector,
	             UInt8 attributes);

	IDTPointer idt;
	IDTEntry*  entries;
};
