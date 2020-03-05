#include "BuddyAlloc.hpp"

#include <Align.hpp>
#include <ValueOf.hpp>

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
	for (UInt8 order = 0; order < BlockOrderCount; ++order) {
		freeBlocks[order.value] = nullptr;
		usedBlocks[order.value] = nullptr;
	}
	unusedBlocks = nullptr;

	// Count number of possible pages
	for (UInt i = 0; i < count; ++i) {
		AddressRange range = rangeList[i.value];

		if (range.type != AddressRange::Type::Usable) {
			continue;
		}

		UIntPtr startPage = (range.base + (1 << PageShift) - 1) >> PageShift;
		UIntPtr endPage   = (range.base + range.length) >> PageShift;
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

		UIntPtr startPage = (range.base + (1 << PageShift) - 1) >> PageShift;
		UIntPtr endPage   = (range.base + range.length) >> PageShift;
		this->initPageRegion(startPage << PageShift, endPage - startPage);
	}
}

BuddyAlloc::~BuddyAlloc() {}

void* BuddyAlloc::allocRegion(UIntPtr address, UInt64 count) {
	UInt64 previousCount;
	while (count > 0) {
		previousCount = count;
		for (UInt8 order = BlockOrderCount - 1; order != UInt8::Max; --order) {
			UInt64 orderPageCount = 1 << order.value;
			UInt64 byteCount      = orderPageCount << PageShift;

			// Find the free block that contains the pages
			PageBlock* current  = nullptr;
			PageBlock* previous = nullptr;
			for (current  = freeBlocks[order.value]; current != nullptr;
			     previous = current, current = current->next) {

				if (current->address <= address &&
				    (current->address + byteCount) > address) {
					break;
				}
				if (current->address > address) {
					current = nullptr;
					break;
				}
			}

			// Did not find Block containing the address
			if (current == nullptr) {
				continue;
			}

			// Remove the Block from the list
			if (previous == nullptr) {
				freeBlocks[order.value] = current->next;
			} else {
				previous->next = current->next;
			}
			current->next = nullptr;

			// If the Block only contains the address, free the memory before
			if (address != current->address) {
				UInt64 freeCount = (address - current->address) >> PageShift;
				this->initPageRegion(current->address, freeCount);

				orderPageCount -= freeCount;
				byteCount = orderPageCount << PageShift;
			}

			// Continue if there is more memory to allocate
			if (count >= orderPageCount) {
				this->setUnusedBlock(current);
				count -= orderPageCount;
				address += byteCount;
				break;
			}

			// Otherwise free the end of the Block
			this->initPageRegion(address + (count << PageShift),
			                     orderPageCount - count);
			this->setUnusedBlock(current);
			return reinterpret_cast<void*>(address.value);
		}

		// FIXME: We can't find the address so we silently skip that page
		if (previousCount == count) {
			--count;
			address += 4096;
		}
	}

	// FIXME: Fail
	return nullptr;
}

void* BuddyAlloc::allocPages(BlockOrder order) {
	for (UInt8 i = ValueOf(order); i < BlockOrderCount; ++i) {
		if (freeBlocks[i.value] == nullptr) {
			continue;
		}

		// Pop block form freeBlocks
		PageBlock* newBlock = freeBlocks[i.value];
		void* returnValue   = reinterpret_cast<void*>(newBlock->address.value);
		freeBlocks[i.value] = newBlock->next;

		// Push block on usedBlocks
		newBlock->next      = usedBlocks[i.value];
		usedBlocks[i.value] = newBlock;

		if (i == ValueOf(order)) {
			return returnValue;
		}

		// Split the block
		UInt64  pagesLeft = (1 << i.value) - (1 << ValueOf(order));
		UIntPtr endAddress =
		    newBlock->address.value + (1 << (i.value + PageShift));
		for (UInt8 j = i - 1; j != UInt8::Max; --j) {
			UInt64 pages = 1 << j.value;
			while (pagesLeft >= pages) {
				PageBlock* newHalfBlock = this->getUnusedBlock();
				newHalfBlock->address   = endAddress - (pages << PageShift);
				endAddress              = newHalfBlock->address;
				this->freeBlock(newHalfBlock, static_cast<BlockOrder>(j.value));

				pagesLeft -= pages;
			}
		}

		return returnValue;
	}

	return nullptr;
}

void BuddyAlloc::freePages(void* pointer) {
	PageBlock* current  = nullptr;
	PageBlock* previous = nullptr;
	UInt64     address  = reinterpret_cast<uintptr_t>(pointer);

	for (UInt8 i = 0; i < BlockOrderCount; ++i) {
		for (current  = usedBlocks[i.value]; current != nullptr;
		     previous = current, current = current->next) {
			if (current->address == address) {
				if (previous == nullptr) {
					usedBlocks[i.value] = current->next;
				} else {
					previous->next = current->next;
				}
				this->freeBlock(current, static_cast<BlockOrder>(i.value));
				return;
			}
		}
	}
	// FIXME: Fail here
}

void BuddyAlloc::initPageRegion(UIntPtr address, UInt64 count) {
	for (UInt8 order = BlockOrderCount - 1; order != UInt8::Max; --order) {
		UInt64 size = 1 << order.value;
		while (count >= size) {
			PageBlock* newBlock = this->getUnusedBlock();

			PageBlock* current  = nullptr;
			PageBlock* previous = nullptr;
			for (current  = freeBlocks[order.value]; current != nullptr;
			     previous = current, current = current->next) {
				if (current->address > address) {
					break;
				}
			}

			newBlock->next    = current;
			newBlock->address = address;
			if (previous == nullptr) {
				freeBlocks[order.value] = newBlock;
			} else {
				previous->next = newBlock;
			}

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

void BuddyAlloc::freeBlock(PageBlock* block, BlockOrder order) {
	PageBlock* current  = nullptr;
	PageBlock* previous = nullptr;

	block->next = nullptr;

	if (freeBlocks[ValueOf(order)] == nullptr) {
		freeBlocks[ValueOf(order)] = block;
		return;
	}

	previous = nullptr;

	// Try to merge blocks
	bool shouldMerge = false;
	for (UInt8 i = ValueOf(order); i < (BlockOrderCount - 1); ++i) {
		UIntPtr buddyAddress = (block->address ^ (1 << (i.value + PageShift)));
		shouldMerge          = false;
		for (current  = freeBlocks[i.value]; current != nullptr;
		     previous = current, current = current->next) {

			if (current->address > block->address) {
				// Found buddy that has a larger address
				if (current->address == buddyAddress) {
					if (previous == nullptr) {
						freeBlocks[i.value] = current->next;
					} else {
						previous->next = current->next;
					}
					current->next = nullptr;

					this->setUnusedBlock(current);
					shouldMerge = true;
					break;
				} else { // Not a buddy
					if (previous == nullptr) {
						freeBlocks[i.value] = block->next;
					} else {
						previous->next = block->next;
					}
					block->next = current;
					return;
				}
			} else if (current->address == buddyAddress) { // Buddy
				if (previous == nullptr) {
					freeBlocks[i.value] = current->next;
				} else {
					previous->next = current->next;
				}
				block->address = current->address;
				this->setUnusedBlock(current);
				shouldMerge = 1;
				break;
			}
		}

		// If shouldMerge we go to the next order
		if (shouldMerge) {
			continue;
		}

		// No buddy, so add the Block to the list
		if (current != nullptr) {
			current->next = block;
		} else {
			freeBlocks[ValueOf(order)] = block;
		}
		return;
	}

	// We got to the highest order and cannot merge anymore
	block->next                = freeBlocks[ValueOf(order)];
	freeBlocks[ValueOf(order)] = block;
}
