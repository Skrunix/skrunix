#pragma once

#include <integers>

class IDT {
  public:
	IDT();
	~IDT();

  private:
	void SetGate(UInt8 number, UIntPtr offset, UInt16 selector,
	             UInt8 attributes);
};
