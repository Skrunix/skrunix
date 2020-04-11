#include "PageAlloc.hpp"

#include "Align.hpp"

PageAlloc::PageAlloc(const char* allocName, const Debug& debugObj)
    : name(allocName)
    , debug(debugObj)
    , freePageCount(0)
    , totalPageCount(0)
    , freeBlocks(nullptr)
    , usedBlocks(nullptr) {}
PageAlloc::~PageAlloc() {}

UIntPtr PageAlloc::alloc(const USize count) {
	this->debug.Write(this->name);
	this->debug.Write(":Alloc ");
	this->debug.WriteHex(count);
	this->debug.Write(" pages...\r\n");

	PageBlock* block = this->freeBlocks;
	while (true) {
		if (block == nullptr) {
			this->debug.Write("Alloc failed! - no free memory\r\n");
			return UIntPtr(0);
		}

		UIntPtr address = block->address;

		// Try to reserve memory
		if (this->reserve(address, count)) {
			return address;
		}

		// Find the next contiguous segment
		block = block->next;
		while (block != nullptr) {
			UIntPtr newAddress = block->address;
			if (newAddress != (address += PageSize)) {
				break;
			}
			block = block->next;
		}
	}

	// TODO: Assert not reached
	this->debug.Write("Alloc failed! - ASSERTION FAILURE\r\n");
	return UIntPtr(0);
}

void PageAlloc::free(const UIntPtr address, const USize count) {
	// TODO: Assert aligned address

	this->debug.Write(this->name);
	this->debug.Write(":Free ");
	this->debug.WriteHex(count);
	this->debug.Write(" pages at ");
	this->debug.WriteHex(address);
	this->debug.Write("\r\n");

	// Find the block for the address
	PageBlock* previousUsed = nullptr;
	PageBlock* usedBlock    = this->usedBlocks;
	while (usedBlock != nullptr) {
		if (usedBlock->address < address) {
			previousUsed = usedBlock;
			usedBlock    = usedBlock->next;
			continue;
		}
		if (usedBlock->address > address) {
			usedBlock = nullptr;
		}
		break;
	}
	if (usedBlock == nullptr) {
		// TODO: Assertion failure
		this->debug.Write("Free failed! - ASSERTION FAILURE\r\n");
		return;
	}

	PageBlock* startBlock = usedBlock; // Save for later

	// Check if there are enough used contiguous blocks
	UIntPtr targetAddress = address;
	for (USize i = 1; i < count; ++i) {
		if (usedBlock == nullptr) {
			// TODO: Assertion failure
			this->debug.Write("Free failed! - NOT ENOUGH USED PAGES\r\n");
			return;
		}
		usedBlock = usedBlock->next;
		targetAddress += PageAlignment;
	}
	if (usedBlock->address != targetAddress) {
		// TODO: Assertion failure
		this->debug.Write(
		    "Free failed! - NOT ENOUGH CONTIGUOUS USED PAGES\r\n");
		return;
	}

	PageBlock* endBlock = usedBlock;       // Save for later
	PageBlock* nextUsed = usedBlock->next; // Save for later

	// Find where to insert the block in the used list
	PageBlock* previousFree = nullptr;
	PageBlock* nextFree     = this->freeBlocks;
	while (nextFree != nullptr) {
		if (nextFree->address < address) {
			previousFree = nextFree;
			nextFree     = nextFree->next;
			continue;
		}
		if (nextFree->address > address) {
			break;
		}
	}

	// Remove from used blocks
	if (previousUsed == nullptr) {
		this->usedBlocks = nextUsed;
	} else {
		previousUsed->next = nextUsed;
	}
	// Insert into free blocks
	if (previousFree == nullptr) {
		this->freeBlocks = startBlock;
	} else {
		previousFree->next = startBlock;
	}
	endBlock->next = nextFree;

	// Update page count
	this->freePageCount += count;
}

bool PageAlloc::reserve(const UIntPtr address, const USize count) {
	// TODO: Assert aligned address
	// TODO: Assert count > 0

	this->debug.Write(this->name);
	this->debug.Write(":Reserve ");
	this->debug.WriteHex(count);
	this->debug.Write(" pages at ");
	this->debug.WriteHex(address);
	this->debug.Write("... ");

	// Find the block for the address
	PageBlock* previousFree = nullptr;
	PageBlock* freeBlock    = this->freeBlocks;
	while (freeBlock != nullptr) {
		if (freeBlock->address < address) {
			previousFree = freeBlock;
			freeBlock    = freeBlock->next;
			continue;
		}
		if (freeBlock->address > address) {
			freeBlock = nullptr;
		}
		break;
	}
	if (freeBlock == nullptr) {
		this->debug.Write("not free\r\n");
		return false;
	}

	PageBlock* startBlock = freeBlock; // Save for later

	// Check if there are enough free contiguous blocks
	UIntPtr targetAddress = address;
	for (USize i = 1; i < count; ++i) {
		if (freeBlock == nullptr) {
			this->debug.Write("not enough free pages\r\n");
			return false;
		}
		freeBlock = freeBlock->next;
		targetAddress += PageAlignment;
	}
	if (freeBlock->address != targetAddress) {
		this->debug.Write("not enough contiguous free pages\r\n");
		return false;
	}

	PageBlock* endBlock = freeBlock;       // Save for later
	PageBlock* nextFree = freeBlock->next; // Save for later

	// Find where to insert the block in the used list
	PageBlock* previousUsed = nullptr;
	PageBlock* nextUsed     = this->usedBlocks;
	while (nextUsed != nullptr) {
		if (nextUsed->address < address) {
			previousUsed = nextUsed;
			nextUsed     = nextUsed->next;
			continue;
		}
		if (nextUsed->address > address) {
			break;
		}
	}

	// Remove from free blocks
	if (previousFree == nullptr) {
		this->freeBlocks = nextFree;
	} else {
		previousFree->next = nextFree;
	}
	// Insert into used blocks
	if (previousUsed == nullptr) {
		this->usedBlocks = startBlock;
	} else {
		previousUsed->next = startBlock;
	}
	endBlock->next = nextUsed;

	// Update page count
	this->freePageCount -= count;

	this->debug.Write("success\r\n");
	return true;
}
