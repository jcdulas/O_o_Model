# One test executable per module; every Catch2 test case is a separate ctest test, so the 1-second timeout applies
# to each of them. Test sources are found by pattern: a new *Test.cpp needs no edit here.
# Always link this executable exclusively against the core, even in a full distribution.
add_executable(oor_memory_check MemoryCheck.cpp)
target_link_libraries(oor_memory_check PRIVATE oor::core)
oor_enable_warnings(oor_memory_check)
oor_link_static_runtime(oor_memory_check)
add_test(NAME reader.memory-only COMMAND oor_memory_check)

foreach(format oos ooh5)
    if(TARGET oor::${format})
        add_executable(oor_${format}_check AdapterCheck.cpp)
        target_link_libraries(oor_${format}_check PRIVATE oor::${format})
        target_compile_definitions(oor_${format}_check PRIVATE OOR_CHECK_${format})
        oor_enable_warnings(oor_${format}_check)
        oor_link_static_runtime(oor_${format}_check)
        add_test(NAME reader.adapter.${format} COMMAND oor_${format}_check "${CMAKE_CURRENT_BINARY_DIR}/check.${format}")
    endif()
endforeach()

if(NOT OOR_ALL_FORMATS)
    return()
endif()
include(Catch)

set(OOR_TEST_MODULES base io deck model results analysis query api)

# Each discovered test runs in its own process and has a one-second wall-clock limit.
set(OOR_TEST_TIMEOUT 1 CACHE STRING "Time limit of each C++ test, in seconds")

foreach(module IN LISTS OOR_TEST_MODULES)
    file(GLOB_RECURSE test_sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${module}/*Test.cpp")
    if(test_sources)
        add_executable(oor_${module}_tests ${test_sources})
        target_link_libraries(oor_${module}_tests PRIVATE oor::${module} Catch2::Catch2WithMain)
        if(NOT module STREQUAL "base" AND NOT module STREQUAL "api")
            target_link_libraries(oor_${module}_tests PRIVATE oor::api)
        endif()
        target_include_directories(oor_${module}_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
        # where the validation models are (tests/cpp/model/ValidationModelsTest.cpp)
        target_compile_definitions(oor_${module}_tests PRIVATE
            OOR_VALIDATION_DIR="${PROJECT_SOURCE_DIR}/validation/models")
        oor_enable_warnings(oor_${module}_tests)
        oor_link_static_runtime(oor_${module}_tests)
        catch_discover_tests(oor_${module}_tests
            DISCOVERY_MODE PRE_TEST
            PROPERTIES TIMEOUT ${OOR_TEST_TIMEOUT})
    endif()
endforeach()
