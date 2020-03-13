#pragma once

#include "IDTEntry.hpp"
#include "IDTPointer.hpp"

#include <Integers/Integers.hpp>

class IDT {
  public:
	IDT(UIntPtr buffer);
	IDT(const IDT&) = delete;
	~IDT();

	IDT& operator=(const IDT&) = delete;

  private:
	void SetGate(UInt8 number, UIntPtr offset, UInt16 selector,
	             UInt8 attributes);

	IDTEntry* entries;
};
