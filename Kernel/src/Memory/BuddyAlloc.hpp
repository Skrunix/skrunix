#pragma once

#include "AddressRange.hpp"

#include <integers>

class BuddyAlloc {
  public:
	BuddyAlloc(AddressRange* rangeList, UInt count);
	~BuddyAlloc();

	UInt64 pageCount;
};
