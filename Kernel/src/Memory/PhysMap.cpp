#include "PhysMap.hpp"

#include "Align.hpp"

struct PageMap {
	UIntPtr phys;
	UIntPtr virt;
};

PhysMap::PhysMap(PhysAlloc* allocator, const UIntPtr kernelStart,
                 const UIntPtr kernelEnd, const UIntPtr kernelOffset,
                 const Debug& debugObj)
    : debug(debugObj)
    , mapCount(0)
    , mapSize(allocator->getTotalPageCount())
    , mapStart(nullptr) {
	// Convert to physical address since the rangeList is all physical
	UIntPtr kernelStartVirt = AlignDown(kernelStart);
	UIntPtr kernelStartPhys = kernelStartVirt - kernelOffset;
	USize   kernelPageCount =
	    (Align(kernelEnd) - kernelStartVirt).value >> PageShift;

	auto pageCount = Align(this->mapSize) >> PageShift;
	auto physPtr   = allocator->alloc(pageCount);
	auto virtPtr   = physPtr + kernelOffset;
	this->mapStart = virtPtr.To<PageMap*>();

	// Map pages we know are in use
	this->map(kernelStartPhys, kernelStartVirt, kernelPageCount);
	this->map(physPtr, virtPtr, pageCount);
}

PhysMap ::~PhysMap() {}

void PhysMap::map(UIntPtr phys, UIntPtr virt, const USize count) {
	// TODO: Assert `this->mapCount + count <= this->mapSize`

	this->debug.Write("Mapping ");
	this->debug.WriteHex(count);
	this->debug.Write(" pages at ");
	this->debug.WriteHex(phys);
	this->debug.Write(" - ");
	this->debug.WriteHex(virt);
	this->debug.Write("\r\n");
	for (USize i = 0; i < count; ++i) {
		this->mapStart[this->mapCount.value].phys = phys;
		this->mapStart[this->mapCount.value].virt = virt;

		phys += PageSize;
		virt += PageSize;
		++this->mapCount;
	}
}

void PhysMap::unmap(UIntPtr phys, UIntPtr virt, const USize count) {
	// TODO: Assert `count >= this->mapCount`

	this->debug.Write("Unmapping ");
	this->debug.WriteHex(count);
	this->debug.Write(" pages at ");
	this->debug.WriteHex(phys);
	this->debug.Write(" - ");
	this->debug.WriteHex(virt);
	this->debug.Write("\r\n");
	for (USize i = 0; i < count; ++i) {
		bool found = false;
		for (USize j = 0; j < this->mapCount; ++j) {
			if (this->mapStart[j.value].phys != phys) {
				continue;
			}
			if (this->mapStart[j.value].virt != virt) {
				continue;
			}

			this->mapStart[j.value] =
			    this->mapStart[(this->mapCount - 1).value];

			phys += PageSize;
			virt += PageSize;
			--this->mapCount;
			found = true;
		}

		// TODO: Assert `found == true`
		if (!found) {
			this->debug.Write("PhysMap - Failed to unmap page\r\n");
		}
	}
}

UIntPtr PhysMap::Virtual(UIntPtr phys) {
	for (USize j = 0; j < this->mapCount; ++j) {
		if (this->mapStart[j.value].phys == phys) {
			return this->mapStart[j.value].virt;
		}
	}
	// TODO: Better error handling
	this->debug.Write("PhysMap - Failed translate ");
	this->debug.WriteHex(phys);
	this->debug.Write(" to Virtual\r\n");
	return 0;
}

UIntPtr PhysMap::Physical(UIntPtr virt) {
	for (USize j = 0; j < this->mapCount; ++j) {
		if (this->mapStart[j.value].virt == virt) {
			return this->mapStart[j.value].phys;
		}
	}
	// TODO: Better error handling
	this->debug.Write("PhysMap - Failed translate ");
	this->debug.WriteHex(virt);
	this->debug.Write(" to Physical\r\n");
	return 0;
}
