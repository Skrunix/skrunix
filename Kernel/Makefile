.DELETE_ON_ERROR:

# Toolchain location
TOOLCHAIN_PATH := $(abspath $(dir $(abspath $(firstword $(MAKEFILE_LIST))))/../toolchain)
TOOLCHAIN_ROOT := $(TOOLCHAIN_PATH)/root
TOOLCHAIN_BIN  := $(TOOLCHAIN_ROOT)/bin

export PATH := $(TOOLCHAIN_BIN):$(PATH)


AS := x86_64-elf-as
CC := x86_64-elf-gcc
CPP := x86_64-elf-g++
LD := x86_64-elf-gcc

ASFLAGS := \
	--fatal-warnings
CFLAGS := \
	-std=c11 \
	-nostdinc \
	-ffreestanding \
	-O2 \
	-Wall \
	-Wextra \
	-Werror \
	-mcmodel=large \
	-mno-red-zone \
	-mno-mmx \
	-mno-sse \
	-mno-sse2
CPPFLAGS := \
	-std=c++17 \
	-nostdinc \
	-iquote src \
	-isystem src/LibC \
	-isystem src/LibCPP \
	-ffreestanding \
	-O2 \
	-Wall \
	-Wextra \
	-Werror \
	-Weffc++ \
	-Waggregate-return \
	-Wcast-align \
	-Wcast-qual \
	-Wchar-subscripts \
	-Wcomment \
	-Wdisabled-optimization \
	-Wfloat-conversion \
	-Wfloat-equal \
	-Wformat \
	-Wformat=2 \
	-Wformat-nonliteral \
	-Wformat-security \
	-Wformat-y2k \
	-Wimport \
	-Winit-self \
	-Winline \
	-Winvalid-pch \
	-Wunsafe-loop-optimizations \
	-Wlong-long \
	-Wmissing-braces \
	-Wmissing-field-initializers \
	-Wmissing-format-attribute \
	-Wmissing-include-dirs \
	-Wmissing-noreturn \
	-Wold-style-cast \
	-Wparentheses \
	-Wpointer-arith \
	-Wredundant-decls \
	-Wreturn-type \
	-Wsequence-point \
	-Wshadow \
	-Wsign-compare \
	-Wstack-protector \
	-Wstrict-aliasing \
	-Wstrict-aliasing=2 \
	-Wswitch \
	-Wswitch-default \
	-Wswitch-enum \
	-Wtrigraphs \
	-Wuninitialized \
	-Wunknown-pragmas \
	-Wunreachable-code \
	-Wunused \
	-Wunused-function \
	-Wunused-label \
	-Wunused-parameter \
	-Wunused-value \
	-Wunused-variable \
	-Wvariadic-macros \
	-Wvolatile-register-var \
	-Wwrite-strings \
	-pedantic \
	-pedantic-errors \
	-mcmodel=large \
	-mno-red-zone \
	-mno-mmx \
	-mno-sse \
	-mno-sse2 \
	-fno-exceptions \
	-fno-rtti
LDFLAGS := \
	-T link.ld \
	-ffreestanding \
	-O2 \
	-nostdlib \
	-lgcc


# $(1) The source folder name
define SrcTemplate =
$(1)_SRC := $(shell find $(1) \( -name *.S -o -name *.c -o -name *.cpp \))
$(1)_OBJ := $$($(1)_SRC:$(1)/%.S=$(1)/.build/%.o)
$(1)_OBJ := $$($(1)_OBJ:$(1)/%.c=$(1)/.build/%.o)
$(1)_OBJ := $$($(1)_OBJ:$(1)/%.cpp=$(1)/.build/%.o)
$(1)_DEP := $$($(1)_SRC:$(1)/%.S=)
$(1)_DEP := $$($(1)_DEP:$(1)/%.c=$(1)/.build/%.d)
$(1)_DEP := $$($(1)_DEP:$(1)/%.cpp=$(1)/.build/%.d)

$(1)_DEPFLAGS = -MT $$@ -MMD -MP -MF $(1)/.build/$$*.d

include $$($(1)_DEP)
$$($(1)_DEP):
	@:

clean::
	rm -rf $(1)/.build

$(1)/.build/%.o: $(1)/%.S
	mkdir -p $(1)/.build
	$(AS) $(ASFLAGS) -o $$@ $$<

$(1)/.build/%.o: $(1)/%.c $(1)/.build/%.d
	mkdir -p $(1)/.build
	$(CC) $$($(1)_DEPFLAGS) $(CFLAGS) -o $$@ -c $$<

$(1)/.build/%.o: $(1)/%.cpp $(1)/.build/%.d
	mkdir -p $(1)/.build
	$(CPP) $$($(1)_DEPFLAGS) $(CPPFLAGS) -o $$@ -c $$<
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
	$(LD) $(LDFLAGS) -o $@ $^
	@echo "\033[0;32mKernel size: "$$((`wc -c <"$@"` +0))" bytes\033[0m"
