# Dependencies used by the in-tree workbook exporter and native tests.
include(FetchContent)

if("xlsx" IN_LIST OOR_FORMATS)
    if(EMSCRIPTEN)
        # zlib from the Emscripten ports (built for the memory model of the build: wasm64 here)
        add_library(ZLIB::ZLIB INTERFACE IMPORTED GLOBAL)
        set_target_properties(ZLIB::ZLIB PROPERTIES
            INTERFACE_COMPILE_OPTIONS "-sUSE_ZLIB=1"
            INTERFACE_LINK_OPTIONS "-sUSE_ZLIB=1")
    else()
        find_package(ZLIB REQUIRED)
    endif()
endif()
if(NOT EMSCRIPTEN)
    find_package(Threads REQUIRED)
endif()

if(OOR_BUILD_TESTS AND OOR_ALL_FORMATS AND NOT EMSCRIPTEN)
    set(CATCH_INSTALL_DOCS OFF CACHE BOOL "" FORCE)
    set(CATCH_INSTALL_EXTRAS OFF CACHE BOOL "" FORCE)
    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.7.1
        GIT_SHALLOW    TRUE)
    FetchContent_MakeAvailable(Catch2)
    list(APPEND CMAKE_MODULE_PATH "${catch2_SOURCE_DIR}/extras")
endif()
