#include "PhysAlloc.hpp"

#include "Align.hpp"
#include "ValueOf.hpp"

PhysAlloc::PhysAlloc(AddressRange* const rangeList, const USize rangeListCount,
                     const UIntPtr kernelStart, const UIntPtr kernelEnd,
                     const UIntPtr kernelOffset, const Debug& debugObj)
    : PageAlloc("Phys", debugObj)
    , pages({}) {

	// Convert to physical address since the rangeList is all physical
	UIntPtr kernelStartPhys = AlignDown(kernelStart) - kernelOffset;
	UIntPtr kernelEndPhys   = Align(kernelEnd) - kernelOffset;
	USize   kernelPageCount =
	    static_cast<uintptr_t>((kernelEndPhys - kernelStartPhys) >> PageShift);
	UIntPtr freePage = kernelEndPhys;

	// Count number of pages
	for (USize i = 0; i < rangeListCount; ++i) {
		AddressRange range = rangeList[static_cast<size_t>(i)];

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
			this->debug.WriteHex(UInt32(ValueOf(range.type)));
		}
		this->debug.Write("\r\n");

		if (range.type != AddressRange::Type::Usable) {
			continue;
		}

		UIntPtr startPage = Align(range.base) >> PageShift;
		UIntPtr endPage   = AlignDown(range.base + range.length) >> PageShift;
		this->totalPageCount += static_cast<uintptr_t>(endPage - startPage);
	}
	this->freePageCount = this->totalPageCount;

	this->debug.Write("RAM Pages: ");
	this->debug.WriteHex(this->totalPageCount);
	this->debug.Write("\r\n");
	this->debug.Write("Tentative allocAddress: ");
	this->debug.WriteHex(freePage);
	this->debug.Write("\r\n");

	// Find a segment of RAM large enough to store all PageBlocks
	Bool    foundBufferLocation = false;
	USize   requiredBufferSize  = this->totalPageCount * sizeof(PageBlock);
	USize   requiredBufferPages = requiredBufferSize >> PageShift;
	UIntPtr allocPage           = freePage >> PageShift;
	for (USize i = 0; i < rangeListCount; ++i) {
		AddressRange range = rangeList[static_cast<size_t>(i)];

		if (range.type != AddressRange::Type::Usable) {
			continue;
		}
		if (range.base + range.length < kernelStartPhys) {
			continue;
		}

		UIntPtr startPage = Align(range.base) >> PageShift;
		UIntPtr endPage   = AlignDown(range.base + range.length) >> PageShift;

		// Check if the range contains allocAddress
		if (startPage <= allocPage && endPage > allocPage) {
			if ((endPage - allocPage) >= requiredBufferPages) {
				// We can fit the data after the kernel
				foundBufferLocation = true;
				break;
			}
			continue;
		}

		// We are checking some other range than where the kernel is loaded
		if ((endPage - startPage) >= requiredBufferPages) {
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
	this->pages.phys = freePage;
	freePage += kernelOffset;
	this->pages.virt  = freePage;
	this->pages.count = Align(requiredBufferSize) >> PageShift;

	// Create all PageBlocks as free pages
	PageBlock* blockBuffer = freePage.To<PageBlock*>();
	USize      index       = -1;
	for (USize i = 0; i < rangeListCount; ++i) {
		AddressRange range = rangeList[static_cast<size_t>(i)];

		if (range.type != AddressRange::Type::Usable) {
			continue;
		}

		UIntPtr start = Align(range.base);
		UIntPtr end   = AlignDown(range.base + range.length);
		for (; start != end; start += PageAlignment) {
			++index;
			blockBuffer[static_cast<size_t>(index)].address = start;
			blockBuffer[static_cast<size_t>(index)].next =
			    &blockBuffer[static_cast<size_t>(index + 1)];
		}
	}
	blockBuffer[static_cast<size_t>(index)].next = nullptr;

	this->freeBlocks = blockBuffer;

	// Reserve pages that we know are in use
	// TODO: Assert true
	this->reserve(kernelStartPhys, kernelPageCount);
	// TODO: Assert true
	this->reserve(freePage - kernelOffset,
	              Align(requiredBufferSize) >> PageShift);
}

PhysAlloc::~PhysAlloc() {}
