add_library(oor_results STATIC
    ModuleInfo.cpp
    # the model of results, whatever the file they come from
    core/ResultLayout.cpp
    core/ResultCatalogue.cpp
    core/ResultCatalogueData.cpp
    core/ResultKind.cpp
    core/ResultFilter.cpp
    core/ResultData.cpp
    core/ResultDecodeStats.cpp
    core/ResultTable.cpp
    core/ResultTables.cpp
    core/NamedResult.cpp
    core/NamedResultKinds.cpp
    core/NamedResultBuilder.cpp
    core/NamedResultFilter.cpp
    core/MatrixResults.cpp
    core/MemoryResults.cpp
    core/MemoryTableIndex.cpp
    attach/ResultAttachment.cpp)
add_library(oor::results ALIAS oor_results)
target_include_directories(oor_results PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>" "$<INSTALL_INTERFACE:include>")
target_link_libraries(oor_results PUBLIC oor_model oor_io)
oor_enable_warnings(oor_results)
