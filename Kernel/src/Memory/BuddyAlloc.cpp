#include "BuddyAlloc.hpp"

#include "BlockOrder.hpp"

#include <Align.hpp>

#define PageShift 12

#include "Serial.hpp"
extern Serial* globalSerial;

#include "Screen.hpp"
extern Screen* screen;

extern UInt64 KernelEnd; // Defined in linker script
void*         allocAddress = &KernelEnd;

PageBlock* freeBlocks[BlockOrderCount] = {0};
PageBlock* usedBlocks[BlockOrderCount] = {0};
PageBlock* unusedBlocks                = nullptr;

BuddyAlloc::BuddyAlloc(AddressRange* rangeList, UInt count)
    : pageCount(0) {
	// Count number of possible pages
	for (UInt i = 0; i < count; ++i) {
		AddressRange range = rangeList[i.value];

		if (range.type != AddressRange::Type::Usable) {
			continue;
		}

		UInt64 startPage = range.base >> PageShift;
		UInt64 endPage   = (range.base + range.length) >> PageShift;

		this->pageCount += (endPage - startPage);
	}

	screen->Write("Tentative allocAddress: ");
	screen->WriteHex(UIntPtr(reinterpret_cast<uintptr_t>(allocAddress)));
	screen->Write("\r\n");

	// Find a segment of RAM large enough to store all PageBlocks
	bool   foundBufferLocation = false;
	UInt64 requiredBufferSize  = this->pageCount * sizeof(PageBlock);
	UInt64 allocPage = reinterpret_cast<uintptr_t>(allocAddress) >> PageShift;
	for (UInt i = 0; i < count; ++i) {
		AddressRange range = rangeList[i.value];

		if (range.type != AddressRange::Type::Usable) {
			continue;
		}

		UInt64 startPage = range.base >> PageShift;
		UInt64 endPage   = (range.base + range.length) >> PageShift;

		// Check if the range contains allocAddress
		if (startPage <= allocPage && endPage > allocPage) {
			if ((endPage - allocPage - 1) << PageShift >= requiredBufferSize) {
				// We can fit the data after the kernel
				foundBufferLocation = true;
				break;
			}
			continue;
		}

		// We are checking some other range than where the kernel is loaded
		if (range.length >= requiredBufferSize) {
			allocAddress        = reinterpret_cast<void*>(range.base.value);
			foundBufferLocation = true;
			break;
		}
	}

	if (foundBufferLocation == false) {
		screen->Write("Could not find space for allocAddress\r\n");
		while (true)
			;
	}

	screen->Write("Real allocAddress:      ");
	screen->WriteHex(UIntPtr(reinterpret_cast<uintptr_t>(allocAddress)));
	screen->Write("\r\n");

	// Create required unusedBlocks for all of RAM
	PageBlock* blockBuffer = Align<PageBlock>(allocAddress, 4096);
	unusedBlocks           = &blockBuffer[0];

	for (UInt64 i = 0; i < (this->pageCount - 1); ++i) {
		blockBuffer[i.value].next = &blockBuffer[i.value + 1];
	}

	// Populate freeBlocks
	for (UInt i = 0; i < count; ++i) {
		AddressRange range = rangeList[i.value];

		if (range.type != AddressRange::Type::Usable) {
			continue;
		}

		UInt64 startPage = range.base >> PageShift;
		UInt64 endPage   = (range.base + range.length) >> PageShift;
		this->initPages(range.base, endPage - startPage);
	}
}

BuddyAlloc::~BuddyAlloc() {}

void BuddyAlloc::initPages(UInt64 address, UInt64 count) {
	for (UInt8 order = BlockOrderCount - 1; order != UInt8::Max; --order) {
		UInt64 size = 1 << order.value;
		while (count > size) {
			PageBlock* newBlock = this->getUnusedBlock();

			newBlock->next    = freeBlocks[order.value];
			newBlock->address = address;

			freeBlocks[order.value] = newBlock;

			address += size << PageShift;
			count -= size;
		}
		if (count == 0) {
			break;
		}
	}
}

PageBlock* BuddyAlloc::getUnusedBlock() {
	auto newBlock = unusedBlocks;
	unusedBlocks  = newBlock->next;
	return newBlock;
}

void BuddyAlloc::setUnusedBlock(PageBlock* block) {
	block->next  = unusedBlocks;
	unusedBlocks = block;
}
