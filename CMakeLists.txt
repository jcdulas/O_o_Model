cmake_minimum_required(VERSION 3.25)

project(oo_model VERSION 0.2.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# The same sources build two ways:
# - natively (GCC or Clang), with the C++ tests: this is where the library is developed and tested;
# - for WebAssembly with Emscripten (`emcmake cmake ...`), which adds the JavaScript module of wasm/.
option(OOR_BUILD_TESTS "Build the C++ tests" ON)
option(OOR_BUILD_WASM "Build the WebAssembly module (Emscripten only)" ${EMSCRIPTEN})
option(OOR_WARNINGS_AS_ERRORS "Treat compiler warnings as errors" ON)
# Notes the slots every card reader and writer uses (tools/oos_layouts/generate_layouts.py); never in a normal build.
option(OOR_TRACE_SLOTS "Trace the slots the card readers and writers use" OFF)
# The time limit of each C++ test, in seconds.
set(OOR_TEST_TIMEOUT 10 CACHE STRING "Time limit of each C++ test, in seconds")

# File adapters shipped with the standard distribution. Empty builds an in-memory Reader.
set(OOR_FORMATS "oos;ooh5;xlsx" CACHE STRING "File adapters to build (oos, ooh5, xlsx)")
foreach(format IN LISTS OOR_FORMATS)
    if(NOT format MATCHES "^(oos|ooh5|xlsx)$")
        message(FATAL_ERROR "Unknown Reader file adapter: ${format}")
    endif()
endforeach()

if("oos" IN_LIST OOR_FORMATS AND "ooh5" IN_LIST OOR_FORMATS AND "xlsx" IN_LIST OOR_FORMATS)
    set(OOR_ALL_FORMATS ON)
endif()

include(OorWarnings)
include(OorDependencies)

# WebAssembly, for every object file and the module:
# - 64-bit WebAssembly (Memory64, "wasm64"): pointers and sizes are 64-bit, so the module can use more than 4 GB of
#   memory (a large deck or result file is held in memory with what is read from it). libhdf5 and zlib are built the same way
#   (scripts/build_hdf5_wasm.sh).
# - native WebAssembly exceptions: C++ exceptions are the library's way to report errors.
if(EMSCRIPTEN)
    add_compile_options(-sMEMORY64=1 -fwasm-exceptions)
    add_link_options(-sMEMORY64=1 -fwasm-exceptions)
endif()

add_subdirectory(src)

option(OOR_BUILD_PYTHON "Build the native CPython extension" OFF)
if(OOR_BUILD_PYTHON)
    add_subdirectory(python)
endif()

if(OOR_BUILD_TESTS AND NOT EMSCRIPTEN)
    enable_testing()
    add_subdirectory(tests/cpp)
endif()

if(OOR_BUILD_WASM)
    if(NOT EMSCRIPTEN)
        message(FATAL_ERROR "OOR_BUILD_WASM needs the Emscripten toolchain: configure with `emcmake cmake`.")
    endif()
    add_subdirectory(wasm)
endif()
