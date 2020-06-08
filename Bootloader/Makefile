.DELETE_ON_ERROR:

# Toolchain location
TOOLCHAIN_PATH := $(abspath $(dir $(abspath $(firstword $(MAKEFILE_LIST))))/../toolchain)
TOOLCHAIN_ROOT := $(TOOLCHAIN_PATH)/root/x86_64-elf
TOOLCHAIN_BIN  := $(TOOLCHAIN_ROOT)/bin

export PATH := $(TOOLCHAIN_BIN):$(PATH)


# $(1) The source folder name
define SrcTemplate =
$(1)_SRC = $(shell find $(1) -name *.S)
$(1)_OBJ = $$($(1)_SRC:$(1)/%.S=$(1)/.build/%.o)

clean::
	rm -rf $(1)/.build

$(1)/.build/%.o: $(1)/%.S
	mkdir -p $(1)/.build
	x86_64-elf-as --fatal-warnings -o $$@ $$<
endef


SRC_FOLDERS = \
	stage1 \
	stage2 \
	common16 \

BINS = \
	bin/stage1.bin \
	bin/stage2.bin \


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

bin/stage1.bin: $(stage1_OBJ) $(common16_OBJ)
	mkdir -p bin/
	x86_64-elf-ld --script link.ld -o $@ $^
	@if [[ $$((`wc -c <"$@"` +0)) -gt 446 ]]; then \
		echo "\033[0;31mERROR: stage1 too large: "$$((`wc -c <"$@"` +0))"/446 bytes\033[0m"; \
		exit 1; \
	else \
		echo "\033[0;32mStage1 size: "$$((`wc -c <"$@"` +0))"/446 bytes\033[0m"; \
	fi

bin/stage2.bin: $(stage2_OBJ) $(common16_OBJ)
	mkdir -p bin/
	x86_64-elf-ld --script link.ld -o $@ $^
	echo "\033[0;32mStage2 size: "$$((`wc -c <"$@"` +0))" bytes\033[0m"
