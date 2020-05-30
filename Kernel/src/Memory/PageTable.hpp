#pragma once

#include "PageTableEntry.hpp"
#include "PhysAlloc.hpp"
#include "PhysMap.hpp"
#include "VirtAlloc.hpp"

class PageTable {
  public:
	PageTable(PhysAlloc& physAlloc, VirtAlloc& virtAlloc, PhysMap& map,
	          UIntPtr kernelStart, UIntPtr kernelEnd, UIntPtr kernelOffset,
	          const Debug& debugObj);
	~PageTable();

	void activate();
	void initMap(UIntPtr phys, UIntPtr virt, USize count = 1);

	void map(UIntPtr phys, UIntPtr virt, USize count = 1);
	void unmap(UIntPtr phys, UIntPtr virt, USize count = 1);

	static void PageTableEntryTest(const Debug& debug);

  private:
	static void ClearPage(UIntPtr);

	const Debug& debug;

	PhysAlloc& physicalAllocator;
	VirtAlloc& virtualAllocator;
	PhysMap&   physicalMap;

	UIntPtr rootPhys;
	UIntPtr koffset;
};
