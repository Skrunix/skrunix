#pragma once

#include "AddressRange.hpp"
#include "BlockOrder.hpp"
#include "PageBlock.hpp"

#include <integers>

class BuddyAlloc {
  public:
	BuddyAlloc(AddressRange* rangeList, UInt count);
	~BuddyAlloc();

	UInt64 pageCount;

  private:
	void initPages(UInt64 address, UInt64 count);

	PageBlock* getUnusedBlock();
	void       setUnusedBlock(PageBlock*);
};
