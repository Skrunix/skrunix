#!/usr/bin/env bash
set -e

# Platform
UNAME=`uname -s`
MACHINE=`gcc -dumpmachine`

# Install location
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
ROOT=$DIR/root
BUILD=$DIR/.build

echo $UNAME
echo $MACHINE
echo $ROOT

# Versions
BINUTILS=binutils-2.35
GCC=gcc-10.2.0

echo $BINUTILS
echo $GCC


# Download sources
mkdir -p sources
pushd sources

if [ ! -f "$BINUTILS.tar.gz" ]; then
	wget https://ftpmirror.gnu.org/binutils/$BINUTILS.tar.gz
fi

if [ ! -f "$GCC.tar.gz" ]; then
	wget https://ftpmirror.gnu.org/gcc/$GCC/$GCC.tar.gz
fi

if [ ! -d "$BINUTILS" ]; then
	tar -xzf $BINUTILS.tar.gz
fi

if [ ! -d "$GCC" ]; then
	tar -xzf $GCC.tar.gz
	cd $GCC && ./contrib/download_prerequisites
fi

popd


# Build native binutils
if [ ! -f "$ROOT/native/bin/ld" ]; then

	# No native binutils on macOS
	if [ "Darwin" != "$UNAME" ]; then

	mkdir -p "$BUILD/native-binutils"
	pushd "$BUILD/native-binutils"

	../../sources/$BINUTILS/configure \
		--disable-nls \
		--disable-multilib \
		--disable-werror \
		--prefix="$ROOT/native" \
		--with-pkgversion="Skrunix Native Binutils"

	make $MAKEFLAGS all           || (echo "Failed to 'make all' in native-binutils"; exit 1)
	make $MAKEFLAGS install-strip || (echo "Failed to 'make install-strip' in native-binutils"; exit 1)

	popd

	fi

fi

# Build native gcc
if [ ! -f "$ROOT/native/bin/gcc" ]; then

	# Special sysroot workaround for macOS
	PLATFORM_ARGS=
	if [ "Darwin" = "$UNAME" ]; then
		PLATFORM_ARGS="--with-sysroot=/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk"
	fi

	mkdir -p "$BUILD/native-gcc"
	pushd "$BUILD/native-gcc"

	../../sources/$GCC/configure \
		--enable-checking=release \
		--enable-languages=c,c++ \
		--disable-nls \
		--disable-multilib \
		--prefix="$ROOT/native" \
		--with-pkgversion="Skrunix Native GCC" \
		$PLATFORM_ARGS

	make $MAKEFLAGS all           || (echo "Failed to 'make all' in native-gcc"; exit 1)
	make $MAKEFLAGS install-strip || (echo "Failed to 'make install-strip' in native-gcc"; exit 1)

	popd

fi


# Add built toolchain to the path
PATH=$ROOT/native/bin:$PATH


# Build x86_64-elf binutils
if [ ! -f "$ROOT/x86_64-elf/bin/x86_64-elf-ld" ]; then

	mkdir -p "$BUILD/x86_64-elf-binutils"
	pushd "$BUILD/x86_64-elf-binutils"

	../../sources/$BINUTILS/configure \
		--disable-nls \
		--disable-multilib \
		--disable-werror \
		--with-sysroot \
		--target="x86_64-elf" \
		--prefix="$ROOT/x86_64-elf" \
		--with-pkgversion="Skrunix x86_64-elf Binutils"

	make $MAKEFLAGS all           || (echo "Failed to 'make all' in x86_64-elf-binutils"; exit 1)
	make $MAKEFLAGS install-strip || (echo "Failed to 'make install-strip' in x86_64-elf-binutils"; exit 1)

	popd

fi

# Build x86_64-elf gcc
if [ ! -f "$ROOT/x86_64-elf/bin/x86_64-elf-gcc" ]; then

	mkdir -p "$BUILD/x86_64-elf-gcc"
	pushd "$BUILD/x86_64-elf-gcc"

	../../sources/$GCC/configure \
		--enable-checking=release \
		--enable-languages=c,c++ \
		--disable-nls \
		--disable-multilib \
		--without-headers \
		--target="x86_64-elf" \
		--prefix="$ROOT/x86_64-elf" \
		--with-pkgversion="Skrunix x86_64-elf GCC"

	make $MAKEFLAGS all-gcc               || (echo "Failed to 'make all-gcc' in x86_64-elf-gcc"; exit 1)
	make $MAKEFLAGS all-target-libgcc     || (echo "Failed to 'make all-target-libgcc' in x86_64-elf-gcc"; exit 1)
	make $MAKEFLAGS install-gcc           || (echo "Failed to 'make install-gcc' in x86_64-elf-gcc"; exit 1)
	make $MAKEFLAGS install-target-libgcc || (echo "Failed to 'make install-target-libgcc' in x86_64-elf-gcc"; exit 1)

	popd

fi


# Build aarch64-none-elf binutils
if [ ! -f "$ROOT/aarch64-none-elf/bin/aarch64-none-elf-ld" ]; then

	mkdir -p "$BUILD/aarch64-none-elf-binutils"
	pushd "$BUILD/aarch64-none-elf-binutils"

	../../sources/$BINUTILS/configure \
		--disable-nls \
		--disable-multilib \
		--disable-werror \
		--with-sysroot \
		--target="aarch64-none-elf" \
		--prefix="$ROOT/aarch64-none-elf" \
		--with-pkgversion="Skrunix aarch64-none-elf Binutils"

	make $MAKEFLAGS all           || (echo "Failed to 'make all' in aarch64-none-elf-binutils"; exit 1)
	make $MAKEFLAGS install-strip || (echo "Failed to 'make install-strip' in aarch64-none-elf-binutils"; exit 1)

	popd

fi

# Build aarch64-none-elf gcc
if [ ! -f "$ROOT/aarch64-none-elf/bin/aarch64-none-elf-gcc" ]; then

	mkdir -p "$BUILD/aarch64-none-elf-gcc"
	pushd "$BUILD/aarch64-none-elf-gcc"

	../../sources/$GCC/configure \
		--enable-checking=release \
		--enable-languages=c,c++ \
		--disable-nls \
		--disable-multilib \
		--without-headers \
		--target="aarch64-none-elf" \
		--prefix="$ROOT/aarch64-none-elf" \
		--with-pkgversion="Skrunix aarch64-none-elf GCC"

	make $MAKEFLAGS all-gcc               || (echo "Failed to 'make all-gcc' in aarch64-none-elf-gcc"; exit 1)
	make $MAKEFLAGS all-target-libgcc     || (echo "Failed to 'make all-target-libgcc' in aarch64-none-elf-gcc"; exit 1)
	make $MAKEFLAGS install-gcc           || (echo "Failed to 'make install-gcc' in aarch64-none-elf-gcc"; exit 1)
	make $MAKEFLAGS install-target-libgcc || (echo "Failed to 'make install-target-libgcc' in aarch64-none-elf-gcc"; exit 1)

	popd

fi


# Build riscv64-none-elf binutils
if [ ! -f "$ROOT/riscv64-none-elf/bin/riscv64-none-elf-ld" ]; then

	mkdir -p "$BUILD/riscv64-none-elf-binutils"
	pushd "$BUILD/riscv64-none-elf-binutils"

	../../sources/$BINUTILS/configure \
		--disable-nls \
		--disable-multilib \
		--disable-werror \
		--with-sysroot \
		--target="riscv64-none-elf" \
		--prefix="$ROOT/riscv64-none-elf" \
		--with-pkgversion="Skrunix riscv64-none-elf Binutils"

	make $MAKEFLAGS all           || (echo "Failed to 'make all' in riscv64-none-elf-binutils"; exit 1)
	make $MAKEFLAGS install-strip || (echo "Failed to 'make install-strip' in riscv64-none-elf-binutils"; exit 1)

	popd

fi

# Build riscv64-none-elf gcc
if [ ! -f "$ROOT/riscv64-none-elf/bin/riscv64-none-elf-gcc" ]; then

	mkdir -p "$BUILD/riscv64-none-elf-gcc"
	pushd "$BUILD/riscv64-none-elf-gcc"

	../../sources/$GCC/configure \
		--enable-checking=release \
		--enable-languages=c,c++ \
		--disable-nls \
		--disable-multilib \
		--without-headers \
		--target="riscv64-none-elf" \
		--prefix="$ROOT/riscv64-none-elf" \
		--with-pkgversion="Skrunix riscv64-none-elf GCC"

	make $MAKEFLAGS all-gcc               || (echo "Failed to 'make all-gcc' in riscv64-none-elf-gcc"; exit 1)
	make $MAKEFLAGS all-target-libgcc     || (echo "Failed to 'make all-target-libgcc' in riscv64-none-elf-gcc"; exit 1)
	make $MAKEFLAGS install-gcc           || (echo "Failed to 'make install-gcc' in riscv64-none-elf-gcc"; exit 1)
	make $MAKEFLAGS install-target-libgcc || (echo "Failed to 'make install-target-libgcc' in riscv64-none-elf-gcc"; exit 1)

	popd

fi

printf "\033[0;32mDone!\033[0m\n"
