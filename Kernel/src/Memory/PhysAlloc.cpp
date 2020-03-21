#include "PhysAlloc.hpp"

#include "Align.hpp"
#include "ValueOf.hpp"

#define PageShift 12

struct PageBlock {
	PageBlock* next;
	UIntPtr    address;
};

PhysAlloc::PhysAlloc(AddressRange* const rangeList, const USize rangeListCount,
                     const UIntPtr kernelStart, const UIntPtr kernelEnd,
                     const UIntPtr kernelOffset, const Debug& debugObj)
    : debug(debugObj)
    , freePageCount(0)
    , totalPageCount(0)
    , freeBlocks(nullptr)
    , usedBlocks(nullptr) {

	// Convert to physical address since the rangeList is all physical
	UIntPtr kernelStartPhys = AlignDown(kernelStart) - kernelOffset;
	UIntPtr kernelEndPhys   = Align(kernelEnd) - kernelOffset;
	USize   kernelPageCount =
	    (kernelEndPhys - kernelStartPhys).value >> PageShift;
	UIntPtr freePage = kernelEndPhys;

	// Count number of pages
	for (USize i = 0; i < rangeListCount; ++i) {
		AddressRange range = rangeList[i.value];

		this->debug.WriteHex(range.base);
		this->debug.Write(" ");
		this->debug.WriteHex(range.length);
		this->debug.Write(" ");
		if (range.type == AddressRange::Type::Usable) {
			this->debug.Write("Usable");
		} else if (range.type == AddressRange::Type::Reserved) {
			this->debug.Write("Reserved");
		} else if (range.type == AddressRange::Type::ACPI_Reclaimable) {
			this->debug.Write("ACPI reclaimable");
		} else if (range.type == AddressRange::Type::ACPI_NVS) {
			this->debug.Write("ACPI NVS");
		} else if (range.type == AddressRange::Type::Bad) {
			this->debug.Write("Bad");
		} else {
			this->debug.Write("? ");
			this->debug.WriteHex(ValueOf(range.type));
		}
		this->debug.Write("\r\n");

		if (range.type != AddressRange::Type::Usable) {
			continue;
		}

		UIntPtr startPage = Align(range.base) >> PageShift;
		UIntPtr endPage   = AlignDown(range.base + range.length) >> PageShift;
		this->totalPageCount += (endPage - startPage).value;
	}
	this->freePageCount = this->totalPageCount;

	this->debug.Write("RAM Pages: ");
	this->debug.WriteHex(this->totalPageCount);
	this->debug.Write("\r\n");
	this->debug.Write("Tentative allocAddress: ");
	this->debug.WriteHex(freePage);
	this->debug.Write("\r\n");

	// Find a segment of RAM large enough to store all PageBlocks
	bool   foundBufferLocation = false;
	USize  requiredBufferSize  = this->totalPageCount * sizeof(PageBlock);
	UInt64 allocPage           = freePage.value >> PageShift;
	for (USize i = 0; i < rangeListCount; ++i) {
		AddressRange range = rangeList[i.value];

		if (range.type != AddressRange::Type::Usable) {
			continue;
		}

		UIntPtr startPage = Align(range.base) >> PageShift;
		UIntPtr endPage   = AlignDown(range.base + range.length) >> PageShift;

		// Check if the range contains allocAddress
		if (startPage <= allocPage && endPage > allocPage) {
			if (((endPage - allocPage) << PageShift) >= requiredBufferSize) {
				// We can fit the data after the kernel
				foundBufferLocation = true;
				break;
			}
			continue;
		}

		// We are checking some other range than where the kernel is loaded
		if (((endPage - startPage) << PageShift) >= requiredBufferSize) {
			freePage            = startPage << PageShift;
			foundBufferLocation = true;
			break;
		}
	}

	// Ensure we have a sufficiently large contiguous block of memory
	if (foundBufferLocation == false) {
		this->debug.Write("Could not find space for allocAddress\r\n");
		while (true)
			;
	}
	this->debug.Write("Real allocAddress:      ");
	this->debug.WriteHex(freePage);
	this->debug.Write("\r\n");

	// Convert back to virtual address
	freePage += kernelOffset;

	// Create all PageBlocks as free pages
	PageBlock* blockBuffer = freePage.To<PageBlock*>();
	USize      index       = USize::Max;
	for (USize i = 0; i < rangeListCount; ++i) {
		AddressRange range = rangeList[i.value];

		if (range.type != AddressRange::Type::Usable) {
			continue;
		}

		UIntPtr start = Align(range.base);
		UIntPtr end   = AlignDown(range.base + range.length);
		for (; start != end; start += PageAlignment) {
			++index;
			blockBuffer[index.value].address = start;
			blockBuffer[index.value].next    = &blockBuffer[(index + 1).value];
		}
	}
	blockBuffer[index.value].next = nullptr;

	this->freeBlocks = blockBuffer;

	// Reserve pages that we know are in use
	// TODO: Assert true
	this->reserve(kernelStartPhys, kernelPageCount);
	// TODO: Assert true
	this->reserve(freePage - kernelOffset,
	              Align(requiredBufferSize) >> PageShift);
}

PhysAlloc::~PhysAlloc() {}

UIntPtr PhysAlloc::alloc(const USize count) {
	// TODO: Implement
	(void)count;
	return UIntPtr(0);
}

void PhysAlloc::free(const UIntPtr address, const USize count) {
	// TODO: Assert aligned address

	// TODO: Implement
	(void)address;
	(void)count;
}

bool PhysAlloc::reserve(const UIntPtr address, const USize count) {
	// TODO: Assert aligned address
	// TODO: Assert count > 0

	this->debug.Write("Reserve ");
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
