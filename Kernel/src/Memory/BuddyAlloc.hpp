#pragma once

#include "AddressRange.hpp"
#include "BlockOrder.hpp"
#include "PageBlock.hpp"

#include <integers>

class BuddyAlloc {
  public:
	BuddyAlloc(AddressRange* rangeList, UInt count);
	~BuddyAlloc();

	void* allocRegion(UIntPtr address, UInt64 count);
	void* allocPages(BlockOrder);
	void  freePages(void*);

	UInt64 pageCount;

  private:
	void initPageRegion(UIntPtr address, UInt64 count);

	PageBlock* getUnusedBlock();
	void       setUnusedBlock(PageBlock*);
	void       freeBlock(PageBlock*, BlockOrder);
};
