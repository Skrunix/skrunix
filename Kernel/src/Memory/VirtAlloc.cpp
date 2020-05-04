#include "VirtAlloc.hpp"

#include "Align.hpp"

VirtAlloc::VirtAlloc(PhysAlloc& allocator, UIntPtr rangeStart,
                     USize rangePageCount, UIntPtr kernelStart,
                     UIntPtr kernelEnd, UIntPtr kernelOffset,
                     const Debug& debugObj)
    : PageAlloc("Virt", debugObj)
    , pages({}) {
	this->freePageCount  = rangePageCount;
	this->totalPageCount = rangePageCount;

	USize requiredBufferSize  = rangePageCount * sizeof(PageBlock);
	USize requiredBufferPages = Align(requiredBufferSize) >> PageShift;

	// Create all PageBlocks as free pages
	UIntPtr    bufferPhys  = allocator.alloc(requiredBufferPages);
	UIntPtr    bufferVirt  = bufferPhys + kernelOffset;
	PageBlock* blockBuffer = bufferVirt.To<PageBlock*>();
	USize      index       = USize::Max;

	this->pages.phys  = bufferPhys;
	this->pages.virt  = bufferVirt;
	this->pages.count = requiredBufferPages;

	UIntPtr start = Align(rangeStart);
	UIntPtr end   = AlignDown(rangeStart + (rangePageCount << PageShift));
	for (; start != end; start += PageAlignment) {
		++index;
		blockBuffer[index.value].address = start;
		blockBuffer[index.value].next    = &blockBuffer[(index + 1).value];
	}
	blockBuffer[index.value].next = nullptr;

	this->freeBlocks = blockBuffer;

	// Convert to physical address since the rangeList is all physical
	UIntPtr kernelStartVirt = AlignDown(kernelStart);
	USize   kernelPageCount =
	    (Align(kernelEnd) - kernelStartVirt).value >> PageShift;

	// Reserve pages that we know are in use
	// TODO: Assert true
	this->reserve(kernelStartVirt, kernelPageCount);
	// TODO: Assert true
	this->reserve(bufferVirt, requiredBufferPages);
}

VirtAlloc::~VirtAlloc() {}
