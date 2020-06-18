#include "PageTable.hpp"

#include "Align.hpp"
#include "CPU.hpp"

PageTable::PageTable(PhysAlloc& physAlloc, VirtAlloc& virtAlloc, PhysMap& map,
                     UIntPtr kernelStart, UIntPtr kernelEnd,
                     UIntPtr kernelOffset, const Debug& debugObj)
    : debug(debugObj)
    , physicalAllocator(physAlloc)
    , virtualAllocator(virtAlloc)
    , physicalMap(map)
    , rootPhys(0)
    , koffset(kernelOffset) {
	// Get physical addresses
	UIntPtr kernelStartPhys = AlignDown(kernelStart) - kernelOffset;
	UIntPtr kernelEndPhys   = Align(kernelEnd) - kernelOffset;
	USize   kernelPageCount =
	    static_cast<uintptr_t>((kernelEndPhys - kernelStartPhys) >> PageShift);

	this->rootPhys = this->physicalAllocator.alloc();
	auto rootVirt  = this->virtualAllocator.alloc();
	this->physicalMap.map(this->rootPhys, rootVirt);
	this->ClearPage(rootPhys + this->koffset);

	this->initMap(this->rootPhys, rootVirt);
	this->initMap(kernelStartPhys, kernelStart, kernelPageCount);
}

PageTable::~PageTable() {
	// TODO: Assert this is not the active table
	// TODO: Deallocate everything
}

void PageTable::activate() { CPU::SetCR3(this->rootPhys); }

void PageTable::map(UIntPtr phys, UIntPtr virt, const USize count) {
	// TODO: unmap and free empty tables
	(void)phys;
	(void)virt;
	(void)count;
}

void PageTable::unmap(const UIntPtr phys, const UIntPtr virt,
                      const USize count) {
	// TODO: unmap and free empty tables
	(void)phys;
	(void)virt;
	(void)count;
}

void PageTable::initMap(UIntPtr phys, UIntPtr virt, const USize count) {
	this->debug.Write("PageTable:Map ");
	this->debug.WriteHex(phys);
	this->debug.Write(" - ");
	this->debug.WriteHex(virt);
	this->debug.Write(" - ");
	this->debug.WriteHex(count);
	this->debug.Write(" pages...\r\n");

	auto p4Table = this->physicalMap.Virtual(this->rootPhys);
	for (USize i = 0; i < count; ++i, phys += PageSize, virt += PageSize) {
		USize offset4 = static_cast<uintptr_t>((virt >> 39) & 0x1FF);
		USize offset3 = static_cast<uintptr_t>((virt >> 30) & 0x1FF);
		USize offset2 = static_cast<uintptr_t>((virt >> 21) & 0x1FF);
		USize offset1 = static_cast<uintptr_t>((virt >> 12) & 0x1FF);

		auto p3Entry = p4Table.To<PageTableEntry*>(offset4);
		if (!p3Entry->GetPresent()) {
			auto tablePhys = this->physicalAllocator.alloc();
			auto tableVirt = tablePhys + this->koffset;
			this->virtualAllocator.reserve(tableVirt);
			this->physicalMap.map(tablePhys, tableVirt);
			this->ClearPage(tablePhys + this->koffset);

			p3Entry->SetPresent(true);
			p3Entry->SetWritable(true);
			p3Entry->SetPhysicalAddress(tablePhys);

			this->initMap(tablePhys, tableVirt);
		}
		auto p3Table = this->physicalMap.Virtual(p3Entry->GetPhysicalAddress());

		auto p2Entry = p3Table.To<PageTableEntry*>(offset3);
		if (!p2Entry->GetPresent()) {
			auto tablePhys = this->physicalAllocator.alloc();
			auto tableVirt = tablePhys + this->koffset;
			this->virtualAllocator.reserve(tableVirt);
			this->physicalMap.map(tablePhys, tableVirt);
			this->ClearPage(tablePhys + this->koffset);

			p2Entry->SetPresent(true);
			p2Entry->SetWritable(true);
			p2Entry->SetPhysicalAddress(tablePhys);

			this->initMap(tablePhys, tableVirt);
		}
		auto p2Table = this->physicalMap.Virtual(p2Entry->GetPhysicalAddress());

		auto p1Entry = p2Table.To<PageTableEntry*>(offset2);
		if (!p1Entry->GetPresent()) {
			auto tablePhys = this->physicalAllocator.alloc();
			auto tableVirt = tablePhys + this->koffset;
			this->virtualAllocator.reserve(tableVirt);
			this->physicalMap.map(tablePhys, tableVirt);
			this->ClearPage(tablePhys + this->koffset);

			p1Entry->SetPresent(true);
			p1Entry->SetWritable(true);
			p1Entry->SetPhysicalAddress(tablePhys);

			this->initMap(tablePhys, tableVirt);
		}
		auto p1Table = this->physicalMap.Virtual(p1Entry->GetPhysicalAddress());

		auto p0Entry = p1Table.To<PageTableEntry*>(offset1);
		// TODO: Assert p0Entry->GetPresent() is false
		p0Entry->SetPresent(true);
		p0Entry->SetWritable(true);
		p0Entry->SetPhysicalAddress(phys);
	}
}

void PageTable::PageTableEntryTest(const Debug& debug) {
	debug.Write("Testing PageTableEntry...\r\n");

	UInt8 failures = 0;

	{
		debug.Write(" - PRESENT      ... ");
		PageTableEntry table(PRESENT);
		if (table.value.fields._present && table.GetPresent()) {
			debug.Write("PASS\r\n");
		} else {
			debug.Write("FAIL\r\n");
			++failures;
		}
	}

	{
		debug.Write(" - WRITABLE     ... ");
		PageTableEntry table(WRITABLE);
		if (table.value.fields._writable && table.GetWritable()) {
			debug.Write("PASS\r\n");
		} else {
			debug.Write("FAIL\r\n");
			++failures;
		}
	}

	{
		debug.Write(" - USERACCESS   ... ");
		PageTableEntry table(USERACCESS);
		if (table.value.fields._userAccessible && table.GetUserAccessible()) {
			debug.Write("PASS\r\n");
		} else {
			debug.Write("FAIL\r\n");
			++failures;
		}
	}

	{
		debug.Write(" - NOWRITECACHE ... ");
		PageTableEntry table(NOWRITECACHE);
		if (table.value.fields._writeThroughCaching &&
		    table.GetWriteThroughCaching()) {
			debug.Write("PASS\r\n");
		} else {
			debug.Write("FAIL\r\n");
			++failures;
		}
	}

	{
		debug.Write(" - NOCACHE      ... ");
		PageTableEntry table(NOCACHE);
		if (table.value.fields._disableCache && table.GetDisableCache()) {
			debug.Write("PASS\r\n");
		} else {
			debug.Write("FAIL\r\n");
			++failures;
		}
	}

	{
		debug.Write(" - ACCESSED     ... ");
		PageTableEntry table(ACCESSED);
		if (table.value.fields._accessed && table.GetAccessed()) {
			debug.Write("PASS\r\n");
		} else {
			debug.Write("FAIL\r\n");
			++failures;
		}
	}

	{
		debug.Write(" - DIRTY        ... ");
		PageTableEntry table(DIRTY);
		if (table.value.fields._dirty && table.GetDirty()) {
			debug.Write("PASS\r\n");
		} else {
			debug.Write("FAIL\r\n");
			++failures;
		}
	}

	{
		debug.Write(" - HUGEPAGE     ... ");
		PageTableEntry table(HUGEPAGE);
		if (table.value.fields._hugePage && table.GetHugePage()) {
			debug.Write("PASS\r\n");
		} else {
			debug.Write("FAIL\r\n");
			++failures;
		}
	}

	{
		debug.Write(" - GLOBAL       ... ");
		PageTableEntry table(GLOBAL);
		if (table.value.fields._global && table.GetGlobal()) {
			debug.Write("PASS\r\n");
		} else {
			debug.Write("FAIL\r\n");
			++failures;
		}
	}

	{
		debug.Write(" - NOEXEC       ... ");
		PageTableEntry table(NOEXEC);
		if (table.value.fields._noExecute && table.GetNoExecute()) {
			debug.Write("PASS\r\n");
		} else {
			debug.Write("FAIL\r\n");
			++failures;
		}
	}

	{
		debug.Write(" - ADDRESS      ... ");
		PageTableEntry table(0);
		table.SetPhysicalAddress(0xFFFF800000000000);
		if (table.GetPhysicalAddress() == 0xFFFF800000000000) {
			debug.Write("PASS\r\n");
		} else {
			debug.Write("FAIL\r\n");
			++failures;
		}
	}

	while (failures > 0)
		;
}

void PageTable::ClearPage(UIntPtr address) {
	auto start = address.To<UInt64*>();
	auto end   = AlignUp(address).To<UInt64*>();
	while (start != end) {
		*start++ = 0;
	}
}
