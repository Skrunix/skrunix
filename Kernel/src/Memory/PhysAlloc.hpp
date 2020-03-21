#pragma once

#include "AddressRange.hpp"
#include "Debug.hpp"

#include <Integers/Integers.hpp>

struct PageBlock;

class PhysAlloc {
  public:
	PhysAlloc(AddressRange* rangeList, USize rangeListCount,
	          UIntPtr kernelStart, UIntPtr kernelEnd, UIntPtr kernelOffset,
	          const Debug& debugObj);
	~PhysAlloc();

	PhysAlloc(const PhysAlloc&) = delete;
	PhysAlloc& operator=(const PhysAlloc&) = delete;

	UIntPtr alloc(USize count = 1);
	void    free(UIntPtr address, USize count = 1);
	bool    reserve(UIntPtr address, USize count = 1);

	USize getFreePageCount() const noexcept { return this->freePageCount; }
	USize getTotalPageCount() const noexcept { return this->totalPageCount; }

  private:
	const Debug& debug;

	USize freePageCount;
	USize totalPageCount;

	PageBlock* freeBlocks;
	PageBlock* usedBlocks;
};
