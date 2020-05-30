# Platform
UNAME := $(shell uname -s)
MACHINE := $(shell $(CC) -dumpmachine)

# Install location
TOOLCHAIN_PATH := $(abspath $(dir $(abspath $(firstword $(MAKEFILE_LIST)))))
TOOLCHAIN_ROOT := $(TOOLCHAIN_PATH)/root
TOOLCHAIN_BIN  := $(TOOLCHAIN_ROOT)/bin

# Special sysroot workaround for macOS
ifeq ($(UNAME),Darwin)
  PLATFORM_ARGS = --with-sysroot=/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk
endif


SENTINELS :=
BINUTILS := binutils-2.34
GCC := gcc-10.1.0

.PHONY: all
all:
	@echo "\033[0;32mDone!\033[0m"

.PHONY: clean
clean:
	rm -rf .build

.PHONY: clean-all
clean-all: clean
	rm -rf $(BINUTILS)
	rm -rf $(GCC)
	rm -f $(SENTINELS)


## Source code

$(BINUTILS).tar.gz:
	wget https://ftpmirror.gnu.org/binutils/$(BINUTILS).tar.gz

$(GCC).tar.gz:
	wget https://ftpmirror.gnu.org/gcc/$(GCC)/$(GCC).tar.gz

$(BINUTILS): $(BINUTILS).tar.gz
	tar -xzf $(BINUTILS).tar.gz

$(GCC): $(GCC).tar.gz
	tar -xzf $(GCC).tar.gz
	cd $@ && ./contrib/download_prerequisites


## Compile

SENTINELS += .binutils-native.sentinel
.binutils-native.sentinel:
# No binutils-native on macOS
ifneq ($(UNAME),Darwin)
	$(MAKE) TARGET=$(MACHINE) .binutils
endif
	@touch $@

SENTINELS += .gcc-native.sentinel
.gcc-native.sentinel: .binutils-native.sentinel
	$(MAKE) TARGET=$(MACHINE) .gcc
	@touch $@

SENTINELS += .binutils-i386-elf.sentinel
.binutils-i386-elf.sentinel: .gcc-native.sentinel
	$(MAKE) TARGET=i386-elf .binutils
	@touch $@

SENTINELS += .binutils-x86_64-elf.sentinel
.binutils-x86_64-elf.sentinel: .gcc-native.sentinel
	$(MAKE) TARGET=x86_64-elf .binutils
	@touch $@

SENTINELS += .gcc-i386-elf.sentinel
.gcc-i386-elf.sentinel: .binutils-i386-elf.sentinel
	$(MAKE) TARGET=i386-elf .gcc
	@touch $@

SENTINELS += .gcc-x86_64-elf.sentinel
.gcc-x86_64-elf.sentinel: .binutils-x86_64-elf.sentinel
	$(MAKE) TARGET=x86_64-elf .gcc
	@touch $@

all: $(SENTINELS)


## Generic compile

.PHONY: .binutils
.binutils: B=.build/$@-$(TARGET)
ifneq ($(MACHINE),$(TARGET))
.binutils: PATH:=$(TOOLCHAIN_BIN):$(PATH)
.binutils: PLATFORM_ARGS += --target=$(TARGET)
endif
.binutils: $(BINUTILS)
	mkdir -p $(B)
	cd $(B) && ../../$(BINUTILS)/configure \
		--disable-nls \
		--disable-multilib \
		--disable-werror \
		--prefix=$(TOOLCHAIN_ROOT) \
		$(PLATFORM_ARGS)
	cd $(B) && $(MAKE) all     || (echo "Failed to 'make all' in $(B)"; exit 1)
	cd $(B) && $(MAKE) install || (echo "Failed to 'make install' in $(B)"; exit 1)

.PHONY: .gcc
.gcc: B=.build/$@-$(TARGET)
ifneq ($(MACHINE),$(TARGET))
.gcc: PATH:=$(TOOLCHAIN_BIN):$(PATH)
.gcc: PLATFORM_ARGS += --target=$(TARGET)
endif
.gcc: $(GCC)
	mkdir -p $(B)
	cd $(B) && ../../$(GCC)/configure \
		--enable-checking=release \
		--enable-languages=c,c++ \
		--disable-nls \
		--disable-multilib \
		--with-pkgversion="Skrunix $(TARGET) GCC" \
		--prefix=$(TOOLCHAIN_ROOT) \
		$(PLATFORM_ARGS)
ifeq ($(MACHINE),$(TARGET))
	cd $(B) && $(MAKE) all                   || (echo "Failed to 'make all' in $(B)"; exit 1)
	cd $(B) && $(MAKE) install-strip         || (echo "Failed to 'make install-strip' in $(B)"; exit 1)
else
	cd $(B) && $(MAKE) all-gcc               || (echo "Failed to 'make all-gcc' in $(B)"; exit 1)
	cd $(B) && $(MAKE) all-target-libgcc     || (echo "Failed to 'make all-target-libgcc' in $(B)"; exit 1)
	cd $(B) && $(MAKE) install-gcc           || (echo "Failed to 'make install-gcc' in $(B)"; exit 1)
	cd $(B) && $(MAKE) install-target-libgcc || (echo "Failed to 'make install-target-libgcc' in $(B)"; exit 1)
endif
