#pragma once

#include "types.h"

class IDT {
  public:
	IDT();
	~IDT();

  private:
	void SetGate(uint8_t number, uintptr_t offset, uint16_t selector,
	             uint8_t attributes);
};
