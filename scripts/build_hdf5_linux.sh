#!/usr/bin/env bash
# Build the HDF5 C API used by the archive adapter, for a native Linux build.
#
# Usage: scripts/build_hdf5_linux.sh <install prefix>
#   Then configure the project with -DCMAKE_PREFIX_PATH=<install prefix>.
#
# The adapter calls functions that HDF5 has from version 1.12 (H5Literate2, H5Oget_info3), and a distribution may
# still package 1.10. The version, the archive and the options are those of build_hdf5_manylinux.sh, which builds
# the library of the Python wheels: a native build then tests the library that is distributed.
# Needs curl, CMake, Ninja, a C compiler and the zlib development files.
set -euo pipefail

if [ $# -ne 1 ]; then
    echo "usage: $0 <install prefix>" >&2
    exit 2
fi
mkdir -p "$1"
prefix="$(cd "$1" && pwd)"

version=1.14.6
work=$(mktemp -d)
trap 'rm -rf "$work"' EXIT
cd "$work"
curl --fail --location --retry 3 -o hdf5.tar.gz \
    "https://github.com/HDFGroup/hdf5/releases/download/hdf5_${version}/hdf5-${version}.tar.gz"
echo 'e4defbac30f50d64e1556374aa49e574417c9e72c6b1de7a4ff88c4b1bea6e9b  hdf5.tar.gz' | sha256sum --check
tar -xzf hdf5.tar.gz
cmake -S "hdf5-${version}" -B build -G Ninja \
    -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX="$prefix" \
    -DCMAKE_POSITION_INDEPENDENT_CODE=ON -DBUILD_SHARED_LIBS=OFF \
    -DBUILD_TESTING=OFF -DHDF5_BUILD_TOOLS=OFF -DHDF5_BUILD_EXAMPLES=OFF \
    -DHDF5_BUILD_UTILS=OFF -DHDF5_BUILD_HL_LIB=OFF -DHDF5_ENABLE_THREADSAFE=ON \
    -DHDF5_ENABLE_Z_LIB_SUPPORT=ON -DHDF5_ENABLE_SZIP_SUPPORT=OFF
cmake --build build --parallel "$(nproc)"
cmake --install build
install -Dm644 "hdf5-${version}/COPYING" "$prefix/share/licenses/hdf5/COPYING"
