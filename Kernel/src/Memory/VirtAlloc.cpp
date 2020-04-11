#include "VirtAlloc.hpp"

#include "Align.hpp"

VirtAlloc::VirtAlloc(PhysAlloc& allocator, UIntPtr rangeStart,
                     USize rangePageCount, UIntPtr kernelStart,
                     UIntPtr kernelEnd, UIntPtr kernelOffset,
                     const Debug& debugObj)
    : PageAlloc("Virt", debugObj) {
	this->freePageCount  = rangePageCount;
	this->totalPageCount = rangePageCount;

	USize requiredBufferSize  = rangePageCount * sizeof(PageBlock);
	USize requiredBufferPages = Align(requiredBufferSize) >> PageShift;

	// Create all PageBlocks as free pages
	UIntPtr    bufferPhys  = allocator.alloc(requiredBufferPages);
	PageBlock* blockBuffer = (bufferPhys + kernelOffset).To<PageBlock*>();
	USize      index       = USize::Max;

	UIntPtr start = Align(rangeStart);
	UIntPtr end   = AlignDown(rangeStart + rangePageCount);
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
	this->reserve(kernelStartVirt, kernelPageCount);
}

VirtAlloc::~VirtAlloc() {}
