#pragma once

#include "AddressRange.hpp"
#include "ContiguousPages.hpp"
#include "Debug.hpp"
#include "PageAlloc.hpp"

#include <Integers/Integers.hpp>

class PhysAlloc : public PageAlloc {
  public:
	PhysAlloc(AddressRange* rangeList, USize rangeListCount,
	          UIntPtr kernelStart, UIntPtr kernelEnd, UIntPtr kernelOffset,
	          const Debug& debugObj);
	~PhysAlloc();

	ContiguousPages pages;
};
