.DELETE_ON_ERROR:

# Toolchain location
TOOLCHAIN_PATH := $(abspath $(dir $(abspath $(firstword $(MAKEFILE_LIST))))/../toolchain)
TOOLCHAIN_ROOT := $(TOOLCHAIN_PATH)/root
TOOLCHAIN_BIN  := $(TOOLCHAIN_ROOT)/bin

export PATH := $(TOOLCHAIN_BIN):$(PATH)


# $(1) The source folder name
define SrcTemplate =
$(1)_SRC := $(shell find $(1) \( -name *.S -o -name *.c -o -name *.cpp \))
$(1)_OBJ := $$($(1)_SRC:$(1)/%.S=$(1)/.build/%.o)
$(1)_OBJ := $$($(1)_OBJ:$(1)/%.c=$(1)/.build/%.o)
$(1)_OBJ := $$($(1)_OBJ:$(1)/%.cpp=$(1)/.build/%.o)

clean::
	rm -rf $(1)/.build

$(1)/.build/%.o: $(1)/%.S
	mkdir -p $(1)/.build
	x86_64-elf-as --fatal-warnings -o $$@ $$<

$(1)/.build/%.o: $(1)/%.c
	mkdir -p $(1)/.build
	x86_64-elf-gcc -o $$@ -c $$< -std=c11 -nostdinc -ffreestanding -O2 -Wall -Wextra -Werror -mcmodel=large -mno-red-zone -mno-mmx -mno-sse -mno-sse2

$(1)/.build/%.o: $(1)/%.cpp
	mkdir -p $(1)/.build
	x86_64-elf-g++ -o $$@ -c $$< -std=c++17 -nostdinc -Isrc -Wp,-v -ffreestanding -O2 -Wall -Wextra -Werror -mcmodel=large -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -fno-exceptions -fno-rtti
endef


SRC_FOLDERS = src
BINS = bin/kernel.bin

.PHONY: all
all: $(BINS)
	@echo "\033[0;32mDone!\033[0m"

.PHONY: clean
clean::
	rm -rf bin


## Generate rules from template

$(foreach _folder, $(SRC_FOLDERS), \
	$(eval $(call SrcTemplate,$(_folder))))


## Link

bin/kernel.bin: $(src_OBJ)
	mkdir -p bin/
	x86_64-elf-gcc -T link.ld -o $@ $^ -ffreestanding -O2 -nostdlib -nostdlib -lgcc
	echo "\033[0;32mKernel size: "$$((`wc -c <"$@"` +0))" bytes\033[0m"
