#pragma once

#include "Debug.hpp"
#include "PhysAlloc.hpp"

#include <Integers/Integers.hpp>

struct PageMap;

class PhysMap {
  public:
	PhysMap(PhysAlloc* allocator, UIntPtr kernelOffset, const Debug& debugObj);
	~PhysMap();

	PhysMap(const PhysMap&) = delete;
	PhysMap& operator=(const PhysMap&) = delete;

	void map(UIntPtr phys, UIntPtr virt, USize count = 1);
	void unmap(UIntPtr phys, UIntPtr virt, USize count = 1);

	UIntPtr Virtual(UIntPtr phys);
	UIntPtr Physical(UIntPtr virt);

  private:
	const Debug& debug;

	USize    mapCount;
	USize    mapSize;
	PageMap* mapStart;
};
