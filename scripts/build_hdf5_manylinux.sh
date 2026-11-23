#!/usr/bin/env bash
# Build the HDF5 C API used by the Reader on the manylinux_2_28 baseline.
set -euo pipefail

version=1.14.6
work=$(mktemp -d)
cd "$work"
curl --fail --location --retry 3 -o hdf5.tar.gz \
    "https://github.com/HDFGroup/hdf5/releases/download/hdf5_${version}/hdf5-${version}.tar.gz"
echo 'e4defbac30f50d64e1556374aa49e574417c9e72c6b1de7a4ff88c4b1bea6e9b  hdf5.tar.gz' | sha256sum --check
tar -xzf hdf5.tar.gz
dnf install -y zlib-devel
/opt/python/cp313-cp313/bin/python -m venv tools
tools/bin/pip install 'cmake>=3.25,<4'
tools/bin/cmake -S "hdf5-${version}" -B build \
    -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local \
    -DCMAKE_POSITION_INDEPENDENT_CODE=ON -DBUILD_SHARED_LIBS=OFF \
    -DBUILD_TESTING=OFF -DHDF5_BUILD_TOOLS=OFF -DHDF5_BUILD_EXAMPLES=OFF \
    -DHDF5_BUILD_UTILS=OFF -DHDF5_BUILD_HL_LIB=OFF -DHDF5_ENABLE_THREADSAFE=ON \
    -DHDF5_ENABLE_Z_LIB_SUPPORT=ON -DHDF5_ENABLE_SZIP_SUPPORT=OFF
tools/bin/cmake --build build --parallel "$(nproc)"
tools/bin/cmake --install build
install -Dm644 "hdf5-${version}/COPYING" /usr/share/licenses/hdf5/COPYING
