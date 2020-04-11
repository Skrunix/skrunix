#pragma once

#include "PageAlloc.hpp"
#include "PhysAlloc.hpp"

class VirtAlloc : public PageAlloc {
  public:
	VirtAlloc(PhysAlloc& allocator, UIntPtr rangeStart, USize rangePageCount,
	          UIntPtr kernelStart, UIntPtr kernelEnd, UIntPtr kernelOffset,
	          const Debug& debugObj);
	~VirtAlloc();
};
