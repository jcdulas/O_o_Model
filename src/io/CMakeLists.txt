add_library(oor_io STATIC
    ModuleInfo.cpp
    binary/Binary.cpp
    files/Files.cpp)
add_library(oor::io ALIAS oor_io)
target_include_directories(oor_io PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(oor_io PUBLIC oor_base)
oor_enable_warnings(oor_io)
