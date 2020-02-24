#include "BuddyAlloc.hpp"

#include "BlockOrder.hpp"
#include "PageBlock.hpp"

PageBlock* freeBlocks[BlockOrderCount] = {0};
PageBlock* usedBlocks[BlockOrderCount] = {0};

BuddyAlloc::BuddyAlloc(AddressRange* rangeList, UInt count)
    : pageCount(0) {
	for (UInt i = 0; i < count; ++i) {
		AddressRange range = rangeList[i.value];

		if (range.type != AddressRange::Type::Usable) {
			continue;
		}

		UInt64 startPage = range.base >> 12;
		UInt64 endPage   = (range.base + range.length) >> 12;

		this->pageCount += (endPage - startPage);
	}
}

BuddyAlloc::~BuddyAlloc() {}
