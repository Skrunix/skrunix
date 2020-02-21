#pragma once

#include <stdint.h>

#define GDT_NULL_SELECTOR 0x00
#define GDT_CODE_SELECTOR 0x08
#define GDT_DATA_SELECTOR 0x10

class GDT {
  public:
	GDT();
	~GDT();

  private:
	void SetEntry(uint8_t number, uint32_t limit, uintptr_t base,
	              uint8_t access, uint8_t flags);
};
