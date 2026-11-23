find_package(Python REQUIRED COMPONENTS Interpreter Development.Module)
execute_process(COMMAND "${Python_EXECUTABLE}" -m pybind11 --cmakedir OUTPUT_VARIABLE pybind11_hint
                OUTPUT_STRIP_TRAILING_WHITESPACE COMMAND_ERROR_IS_FATAL ANY)
find_package(pybind11 CONFIG REQUIRED HINTS "${pybind11_hint}")
pybind11_add_module(_native MODULE NO_EXTRAS bindings.cpp)
target_link_libraries(_native PRIVATE oor_api)
install(TARGETS _native LIBRARY DESTINATION oor_reader RUNTIME DESTINATION oor_reader)

# Include the notices for libraries bundled by repair tools on the binary-wheel platforms.
if(MINGW)
    get_filename_component(compiler_dir "${CMAKE_CXX_COMPILER}" DIRECTORY)
    set(license_root "${compiler_dir}/../share/licenses")
    set(runtime_packages gcc-libs winpthreads hdf5 libaec zlib zlib-ng aws-c-auth aws-c-cal aws-c-common
        aws-c-compression aws-c-http aws-c-io aws-c-s3 aws-c-sdkutils aws-checksums)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(license_root "/usr/share/licenses")
    set(runtime_packages hdf5 libaec szip zlib)
endif()
foreach(package IN LISTS runtime_packages)
    if(IS_DIRECTORY "${license_root}/${package}")
        install(DIRECTORY "${license_root}/${package}" DESTINATION oor_reader/licenses)
    endif()
endforeach()
