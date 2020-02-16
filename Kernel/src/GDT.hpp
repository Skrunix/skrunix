#pragma once

#include <stdint.h>

class GDT {
  public:
	GDT();
	~GDT();

  private:
	void SetEntry(uint8_t number, uint32_t limit, uintptr_t base,
	              uint8_t access, uint8_t flags);
};
