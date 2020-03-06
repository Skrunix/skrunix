#pragma once

#include "AddressRange.hpp"
#include "BlockOrder.hpp"
#include "PageBlock.hpp"

#include <Integers.hpp>

class BuddyAlloc {
  public:
	BuddyAlloc(AddressRange* rangeList, USize count);
	~BuddyAlloc();

	void* allocRegion(UIntPtr address, USize count);
	void* allocPages(BlockOrder);
	void  freePages(void*);

	USize pageCount;

  private:
	void initPageRegion(UIntPtr address, USize count);

	PageBlock* getUnusedBlock();
	void       setUnusedBlock(PageBlock*);
	void       freeBlock(PageBlock*, BlockOrder);
};
