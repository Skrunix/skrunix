.DELETE_ON_ERROR:

DISK = disk.hdd

.PHONY: all
all: $(DISK)
	@echo "\033[0;32mDone!\033[0m"

.PHONY: clean
clean:
	rm -f $(DISK)


## Temporary: Just dd the bins into a larger file

$(DISK): Bootloader/bin/stage1.bin Bootloader/bin/stage2.bin Kernel/bin/kernel.bin
	touch $@
	dd if=/dev/zero of=$@ bs=512 count=100 conv=notrunc >& /dev/null
	dd if=Bootloader/bin/stage1.bin of=$@ bs=1 count=510 conv=notrunc >& /dev/null
	printf '\x55\xAA' | dd of=$@ bs=1 seek=510 count=2 conv=notrunc >& /dev/null
	dd if=Bootloader/bin/stage2.bin of=$@ bs=512 seek=1 count=10 conv=notrunc >& /dev/null
	dd if=Kernel/bin/kernel.bin of=$@ bs=512 seek=11 count=80 conv=notrunc >& /dev/null


## Run
# -S -s -D log -d int --no-reboot -no-shutdown

.PHONY: run
run: $(DISK) qemu-bios/bin/a20on.bin
	qemu-system-x86_64 \
		-chardev stdio,mux=on,id=char0 \
		-mon chardev=char0,mode=readline \
		-serial chardev:char0 \
		-drive format=raw,file=$(DISK)


## Build Dependencies

.PHONY: Bootloader/bin/stage1.bin
Bootloader/bin/stage1.bin:
	$(MAKE) -C Bootloader bin/stage1.bin

.PHONY: Bootloader/bin/stage2.bin
Bootloader/bin/stage2.bin:
	$(MAKE) -C Bootloader bin/stage2.bin

.PHONY: Kernel/bin/kernel.bin
Kernel/bin/kernel.bin:
	$(MAKE) -C Kernel bin/kernel.bin

qemu-bios/bin/a20on.bin:
	$(MAKE) -C qemu-bios bin/a20on.bin

qemu-bios/bin/a20off.bin:
	$(MAKE) -C qemu-bios bin/a20off.bin
