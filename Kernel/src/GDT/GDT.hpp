#pragma once

#include <Integers.hpp>

#define GDT_NULL_SELECTOR 0x00
#define GDT_CODE_SELECTOR 0x08
#define GDT_DATA_SELECTOR 0x10

class GDT {
  public:
	GDT();
	~GDT();

  private:
	void SetEntry(UInt8 number, UInt32 limit, UIntPtr base, UInt8 access,
	              UInt8 flags);
};
