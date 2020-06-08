# Toolchain location
TOOLCHAIN_PATH := $(abspath $(dir $(abspath $(firstword $(MAKEFILE_LIST))))/../toolchain)
TOOLCHAIN_ROOT := $(TOOLCHAIN_PATH)/root/x86_64-elf
TOOLCHAIN_BIN  := $(TOOLCHAIN_ROOT)/bin

export PATH := $(TOOLCHAIN_BIN):$(PATH)


SEABIOS := seabios-rel-1.13.0

.PHONY: all
all: bin/a20on.bin bin/a20off.bin
	@echo "\033[0;32mDone!\033[0m"

.PHONY: clean
clean:
	rm -rf .build

.PHONY: clean-all
clean-all: clean
	rm -rf $(SEABIOS)


## Source code

$(SEABIOS).tar.gz:
	wget https://git.seabios.org/cgit/seabios.git/snapshot/$(SEABIOS).tar.gz

$(SEABIOS): $(SEABIOS).tar.gz
	tar -xzf $(SEABIOS).tar.gz


## Compile

.NOTPARALLEL: .build/a20on/bios.bin
.build/a20on/bios.bin: $(SEABIOS)
	$(MAKE) -C $(SEABIOS) CROSS_PREFIX=x86_64-elf- defconfig
	cd $(SEABIOS) && ./scripts/kconfig/merge_config.sh -m .config ../configs/a20on
	$(MAKE) -C $(SEABIOS) CROSS_PREFIX=x86_64-elf- EXTRAVERSION="-skrunix-a20on" OUT=../.build/a20on/

.NOTPARALLEL: .build/a20off/bios.bin
.build/a20off/bios.bin: $(SEABIOS)
	$(MAKE) -C $(SEABIOS) CROSS_PREFIX=x86_64-elf- defconfig
	cd $(SEABIOS) && ./scripts/kconfig/merge_config.sh -m .config ../configs/a20off
	$(MAKE) -C $(SEABIOS) CROSS_PREFIX=x86_64-elf- EXTRAVERSION="-skrunix-a20off" OUT=../.build/a20off/


## Copy

bin/%.bin: .build/%/bios.bin
	mkdir -p bin
	cp $^ $@
